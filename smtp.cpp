#include "smtp.h"
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QByteArray>

Smtp::Smtp(const QString &user, const QString &pass, const QString &host, int port, int timeout)
{
    socket = new QSslSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReceived(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    this->user = user;
    this->pass = pass;
    this->host = host;
    this->port = port;
    this->timeout = timeout;
}

void Smtp::sendMail(const QString &from, const QString &to, const QString &subject, const QString &body, QStringList files)
{
    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");

    // Initialize multipart MIME with boundary "frontier"
    message.append("MIME-Version: 1.0\n");
    message.append("Content-Type: multipart/mixed; boundary=frontier\n\n");

    message.append("--frontier\n");
    message.append("Content-Type: text/plain\n\n");
    message.append(body);
    message.append("\n\n");

    // Attach files
    if (!files.isEmpty())
    {
        qDebug() << "Files to be sent: " << files.size();
        foreach (QString filePath, files)
        {
            QFile file(filePath);
            if (file.exists())
            {
                if (!file.open(QIODevice::ReadOnly))
                {
                    qDebug("Couldn't open the file");
                    QMessageBox::warning(0, tr("SMTP Client"), tr("Couldn't open the file\n\n"));
                    return;
                }
                QByteArray bytes = file.readAll();
                message.append("--frontier\n");
                message.append("Content-Type: application/octet-stream\nContent-Disposition: attachment; filename=" + QFileInfo(file.fileName()).fileName() + ";\nContent-Transfer-Encoding: base64\n\n");
                message.append(bytes.toBase64());
                message.append("\n");
            }
        }
    }
    else
    {
        qDebug() << "No attachments found";
    }

    message.append("--frontier--\n");

    // Replace line endings as required by SMTP
    message.replace(QString::fromLatin1("\n"), QString::fromLatin1("\r\n"));
    message.replace(QString::fromLatin1("\r\n.\r\n"), QString::fromLatin1("\r\n..\r\n"));

    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHostEncrypted(host, port); // SMTP host and port for TLS
    if (!socket->waitForConnected(timeout))
    {
        qDebug() << socket->errorString();
    }

    t = new QTextStream(socket);
}

Smtp::~Smtp()
{
    delete t;
    delete socket;
}

void Smtp::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "State changed: " << socketState;
}

void Smtp::errorReceived(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error: " << socketError;
}

void Smtp::disconnected()
{
    qDebug() << "Disconnected";
    qDebug() << "Error: " << socket->errorString();
}

void Smtp::connected()
{
    qDebug() << "Connected to SMTP server.";
}

void Smtp::readyRead()
{
    qDebug() << "Ready to read server response.";

    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    } while (socket->canReadLine() && responseLine[3] != ' ');

    responseLine.truncate(3);

    qDebug() << "Server response code: " << responseLine;
    qDebug() << "Server response: " << response;

    // Handle SMTP states
    if (state == Init && responseLine == "220")
    {
        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = HandShake;
    }
    else if (state == HandShake && responseLine == "250")
    {
        socket->startClientEncryption();
        if (!socket->waitForEncrypted(timeout))
        {
            qDebug() << socket->errorString();
            state = Close;
        }

        *t << "EHLO localhost" << "\r\n";
        t->flush();
        state = Auth;
    }
    else if (state == Auth && responseLine == "250")
    {
        qDebug() << "Starting authentication";
        *t << "AUTH LOGIN" << "\r\n";
        t->flush();
        state = User;
    }
    else if (state == User && responseLine == "334")
    {
        qDebug() << "Sending username";
        QByteArray encodedUsername = QByteArray::fromStdString(user.toStdString()).toBase64();
        *t << encodedUsername << "\r\n";
        t->flush();
        state = Pass;
    }
    else if (state == Pass && responseLine == "334")
    {
        qDebug() << "Sending password";
        QByteArray encodedPassword = QByteArray::fromStdString(pass.toStdString()).toBase64();
        *t << encodedPassword << "\r\n";
        t->flush();
        state = Mail;
    }
    else if (state == Mail && responseLine == "235")
    {
        qDebug() << "Authenticated. Sending MAIL FROM.";
        *t << "MAIL FROM:<" << from << ">\r\n";
        t->flush();
        state = Rcpt;
    }
    else if (state == Rcpt && responseLine == "250")
    {
        *t << "RCPT TO:<" << rcpt << ">\r\n";
        t->flush();
        state = Data;
    }
    else if (state == Data && responseLine == "250")
    {
        *t << "DATA\r\n";
        t->flush();
        state = Body;
    }
    else if (state == Body && responseLine == "354")
    {
        *t << message << "\r\n.\r\n";
        t->flush();
        state = Quit;
    }
    else if (state == Quit && responseLine == "250")
    {
        *t << "QUIT\r\n";
        t->flush();
        state = Close;
        emit status(tr("Message sent"));
    }
    else if (state == Close)
    {
        deleteLater();
        return;
    }
    else
    {
        QMessageBox::warning(0, tr("SMTP Client"), tr("Unexpected reply from SMTP server:\n\n") + response);
        state = Close;
        emit status(tr("Failed to send message"));
    }
    response = "";
}
