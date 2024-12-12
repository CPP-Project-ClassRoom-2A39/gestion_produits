#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QRegularExpressionValidator>
#include<QDebug>
#include"produit.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QPainter>
#include<QVBoxLayout>
#include "Operation/Operation.h"
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    serialbuffer="";
        QString portName;
           foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
               if (info.portName() == "COM6") {
                   portName = info.portName();
                   break;
               }
           }

           if (portName.isEmpty()) {
               qDebug() << "COM6 not found.";
           }
              serialPort = new QSerialPort(portName);
              serialPort->setBaudRate(QSerialPort::Baud9600);
              serialPort->setDataBits(QSerialPort::Data8);
              serialPort->setParity(QSerialPort::NoParity);
              serialPort->setStopBits(QSerialPort::OneStop);
             connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readarduino);
              // Open the serial port
              if (!serialPort->open(QIODevice::ReadWrite)) {
                  qDebug() << "Failed to open the serial port.";
                  delete serialPort;

              }

////////////////controle saisie
    QRegularExpression regex("^[a-z-@]*$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, ui->name );
    ui->setupUi(this);
    ///////////////////
ui->pushButton_7->setText("manually");
    toggle_ard=0;
    ui->statis->setVisible(false);
///////////////to modify
///
    ui->export_2->setVisible(true);
    //ui->label_2->setVisible(true);

    ui->statis_2->setVisible(false);

    ui->list_butt_3->setEnabled(false);
    //ui->numb_notif->setText(  QString::number(E.get_product_number()));
    ////////////
    ui->delete_conf->setVisible(false);
    ui->delete_ok->setEnabled(false);
    ui->cancel_delt->setEnabled(false);
    ui->tableView->setModel(E.afficher("",0));
    ui->unable_to_add->setVisible(false);
    ui->ID->setValidator(new QIntValidator(12, 9999999, this));
    //ui->name->setValidator(validator);
    ui->price->setValidator(new QIntValidator(8, 9999999, this));
    ui->quantity->setValidator(new QIntValidator(8, 9999999, this));
    ui->search->setValidator(new QIntValidator(12, 9999999, this));
    ui->cancel_delt_2->setVisible(false);
    ui->cancel_delt_2->setEnabled(false);
    ui->delete_ok_2->setVisible(false);
    ui->delete_ok_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
 E.toggle_notif_bar=0;

    //////////statistic
    ///
    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);
    QString number=QString::number(10);
    //////to modify
    QString male ={"male :%"};
    QString number2=QString::number(7);
    QString female ={"female :%"};
    //////
    male+=number;
    female+=number2;
    ////to modify
    series->append(male,7);
    series->append(female,8);
    QString number3=QString::number(15);;
    QString total{"total employees:%"};
    ////
    total+=number3;
    QPieSlice *slice =series->append(total,100);
    slice->setExploded();
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("example");
    QChartView *charview = new QChartView(chart);
    charview->setRenderHint(QPainter::Antialiasing);
    charview->setParent(ui->horizontalFrame);
///////////////////////client
///
    ui->statis_c->setVisible(false);
    ui->export_2->setVisible(true);
    ui->statis_2_c->setVisible(false);
    ui->list_butt_3_c->setEnabled(false);
    ////////////
    ui->delete_conf_c->setVisible(false);
    ui->delete_ok_c->setEnabled(false);
    ui->cancel_delt_c->setEnabled(false);
    ui->tableView_c->setModel(C.afficher("",0));
    ui->ID_c->setValidator(new QIntValidator(12, 9999999, this));
    ui->name_c->setValidator(validator);
    ui->last_name_c->setValidator(validator);
    ui->number_c->setValidator(new QIntValidator(12, 9999999, this));
    ui->mail_c->setValidator(validator);
    ui->search_c->setValidator(new QIntValidator(12, 9999999, this));
    ui->cancel_delt_2_c->setVisible(false);
    ui->cancel_delt_2_c->setEnabled(false);
    ui->delete_ok_2_c->setVisible(false);
    ui->delete_ok_2_c->setEnabled(false);
    ui->pushButton_c->setEnabled(false);





/////////////////////:client

    ui->statis_c->setVisible(false);

    ui->export_2_c->setVisible(true);


    ui->statis_2_c->setVisible(false);

    ui->list_butt_3_c->setEnabled(false);

    ////////////
    ui->delete_conf_c->setVisible(false);
    ui->delete_ok_c->setEnabled(false);
    ui->cancel_delt_c->setEnabled(false);
    ui->tableView_c->setModel(C.afficher("",0));
    ui->ID_c->setValidator(new QIntValidator(12, 9999999, this));
    ui->name_c->setValidator(validator);
    ui->last_name_c->setValidator(validator);
    ui->number_c->setValidator(new QIntValidator(12, 9999999, this));
    ui->mail_c->setValidator(validator);
    ui->search_c->setValidator(new QIntValidator(12, 9999999, this));
    ui->cancel_delt_2_c->setVisible(false);
    ui->cancel_delt_2_c->setEnabled(false);
    ui->delete_ok_2_c->setVisible(false);
    ui->delete_ok_2_c->setEnabled(false);
    ui->pushButton_c->setEnabled(false);




    //////////statistic


/////////////fournisseur
///
    ui->statis_f->setVisible(false);

    ui->export_f->setVisible(true);

    ui->statis_f->setVisible(false);

    ui->list_butt_f->setEnabled(false);

    ////////////
    ui->delete_conf_f->setVisible(false);
    ui->delete_ok_f->setEnabled(false);
    ui->cancel_delt_f->setEnabled(false);
    ui->tableView_f->setModel(F.afficher("",0));
    ui->ID_f->setValidator(new QIntValidator(12, 9999999, this));

    ui->number_f_2->setValidator(new QIntValidator(12, 9999999, this));
    //ui->mail_f_2->setValidator(validator);
    ui->search_f->setValidator(new QIntValidator(12, 9999999, this));

    ui->delete_ok_f->setVisible(false);
    ui->pushButton_f->setEnabled(false);




    //////////statistic
    ///





}



MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_Delete_button_clicked()
{
    ui->delete_conf->setVisible(true);
    ui->delete_ok->setEnabled(true);
    ui->cancel_delt->setEnabled(true);
    ui->delete_ok->setVisible(true);
    //ui->employe_wid->setCurrentIndex(1);
}




void MainWindow::on_delete_ok_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
      produit em;
       model->setQuery("select * from produit");
       ui->delete_ok->setVisible(false);
       ui->cancel_delt->setEnabled(false);
       ui->delete_conf->setVisible(false);
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    QVariant data = model->data(index, Qt::DisplayRole);
    QString deleted_data=data.toString();
    em.delete_product(deleted_data);
    ui->tableView->setModel(E.afficher("",0));
    index=QModelIndex();

}

void MainWindow::on_cancel_delt_clicked()
{
    ui->delete_conf->setVisible(false);
    ui->delete_ok->setEnabled(false);
    ui->cancel_delt->setEnabled(false);
}

void MainWindow::on_modify_button_clicked()
{

    QString id;
    QString name;
    QString quantite;
    QString price;
    QDate date_a;
    QDate date_e;

    produit em;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from produit");
    E.set_mode_add(2);
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
     QModelIndex columnIndex = model->index(index.row(), 0);
     if (index.isValid()) {

    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    id=data.toString();
    ui->ID->setText(id);
    columnIndex = model->index(index.row(), 1);
    data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 2);
    data = model->data(columnIndex, Qt::DisplayRole);
    price=data.toString();

    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    quantite=data.toString();

    columnIndex = model->index(index.row(), 4);
    data = model->data(columnIndex, Qt::DisplayRole);
    date_a=data.toDate();


    columnIndex = model->index(index.row(), 5);
    data = model->data(columnIndex, Qt::DisplayRole);
    date_e=data.toDate();

     ui->ID->setReadOnly(true);
     ui->name->setText(name);
     ui->price->setText(price);
     ui->quantity->setText(quantite);
     ui->date_a_label->setDate(date_a);
     ui->date_e_label->setDate(date_e);


     int valueToSend = quantite.toInt();

     QString name2 = name;

     QByteArray tosd = QByteArray::number(valueToSend) + '\n';


     QByteArray tosd2 = name2.toUtf8() + '\n';


     QByteArray combinedData = tosd + "," + tosd2;

     qDebug() << "Sending combined data:" << combinedData;


     serialPort->write(combinedData);
}
}

void MainWindow::on_return_to_list_clicked()
{



    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from produit");

    QModelIndex index = ui->tableView->selectionModel()->currentIndex();

    model->setData(index, QVariant(), Qt::EditRole);


}

void MainWindow::on_add_employe_clicked()
{
    E.set_mode_add(1);
    produit em;
    QString dateString = ui->date_a_label->text();
    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");
    QString dateString2 = ui->date_e_label->text();
    QDate date2 = QDate::fromString(dateString2, "dd/MM/yyyy");

    if(E.get_mode_add()==2){
    em.set_id(ui->ID->text());
    em.set_name(ui->name->text());
    em.setPrix_u(ui->price->text().toUInt());
    em.setQuantite_p(ui->quantity->text().toUInt());
    em.setDate_a(date);
    em.setDate_e(date2);
        bool test=em.update_product();

           }


     if(E.get_mode_add()==1){
        E.set_id(ui->ID->text());
        E.set_name(ui->name->text());
        E.setPrix_u(ui->price->text().toUInt());
        E.setQuantite_p(ui->quantity->text().toUInt());
        E.setDate_a(date);
        E.setDate_e(date2);

        E.add_product();


        int test=E.get_if_emp_added();

            if(test==1 )
            {
                ui->unable_to_add->setVisible(true);
                ui->unable_to_add->setEnabled(true);
                ui->cancel_delt_2->setVisible(true);
                ui->cancel_delt_2->setEnabled(true);
                ui->delete_ok_2->setVisible(true);
                ui->delete_ok_2->setEnabled(true);
                 qInfo()<<E.getPrix_u();
                  qInfo()<<dateString;

            }


        if(test==0 ){
        ui->unable_to_add->setVisible(true);
        ui->unable_to_add->setEnabled(true);
        ui->cancel_delt_2->setVisible(true);
        ui->cancel_delt_2->setEnabled(true);
        ui->delete_ok_2->setVisible(true);
        ui->delete_ok_2->setEnabled(true);}





    }

    ui->tableView->setModel(E.afficher("",0));
   // ui->employe_wid->setCurrentIndex(3);

}

void MainWindow::on_add_emp_clicked()
{

    ui->ID->setReadOnly(false);
    E.set_mode_add(1);
    ui->employe_wid->setCurrentIndex(1);
    ui->ID->setText("");
    ui->name->setText("");
    ui->price->setText("");
    ui->quantity->setText("");


}

void MainWindow::sendmailtoallfournisseur(const QString &text)
{
    Smtp* smtp = new Smtp("hnachamine@gmail.com","nxem iunr dsyv vmvy", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    qInfo()<<"size of mails"<< E.list_mail_fournisseur().size();


    for (int i = 0; i < E.list_mail_fournisseur().size(); ++i) {
           QString email = E.list_mail_fournisseur().at(i);
           smtp->sendMail("hnachamine@gmail.com", email, "", text + " is running out of stock");
           qInfo()<<"mails"<<E.list_mail_fournisseur().at(i);
       }
    disconnect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

}





void MainWindow::on_return_to_list_2_clicked()
{
    ui->employe_wid->setCurrentIndex(1);
}


void MainWindow::on_search_butt_clicked()
{
    QString data;
    data=ui->search->text();
    if(data=="")
            E.set_view_mode(0);
     else
            E.set_view_mode(1);
    ui->tableView->setModel(E.afficher(data,E.get_view_mode()));
}

void MainWindow::on_refresh_emp_clicked()
{
    QString name;
    QString price;
    QString quantite;
    QString date_e;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->clear();
    model->setQuery("select * from produit");
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    qInfo()<<index;
     if (index.isValid()) {
    QModelIndex columnIndex = model->index(index.row(), 1);
    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 2);
    data = model->data(columnIndex, Qt::DisplayRole);
    price=data.toString();
    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    quantite=data.toString();
    columnIndex = model->index(index.row(), 5);
    data = model->data(columnIndex, Qt::DisplayRole);
    date_e=data.toString();

     }

}
void MainWindow::set_stars(QString data)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from employe");
    E.set_mode_add(1);
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
     QModelIndex columnIndex = model->index(index.row(), 0);
     QVariant data1=model->data(columnIndex,Qt::DisplayRole);
     QString data2=data1.toString();
     qInfo()<<data2;
     E.set_id(data2);
     ui->tableView->setModel(E.afficher("",0));
}



void MainWindow::on_list_butt_clicked()
{
    ui->employe_wid->setCurrentIndex(0);
}

void MainWindow::on_statis_butt_clicked()
{
  ui->employe_wid->setCurrentIndex(2);
}

void MainWindow::on_list_butt_2_clicked()
{
    ui->employe_wid->setCurrentIndex(0);
}

void MainWindow::on_cancel_delt_2_clicked()
{
    ui->unable_to_add->setVisible(false);
    ui->unable_to_add->setEnabled(false);
    ui->cancel_delt_2->setVisible(false);
    ui->cancel_delt_2->setEnabled(false);
    ui->delete_ok_2->setVisible(false);
    ui->delete_ok_2->setEnabled(false);
}

void MainWindow::on_delete_ok_2_clicked()
{
    ui->unable_to_add->setVisible(false);
    ui->unable_to_add->setEnabled(false);
    ui->cancel_delt_2->setVisible(false);
    ui->cancel_delt_2->setEnabled(false);
    ui->delete_ok_2->setVisible(false);
    ui->delete_ok_2->setEnabled(false);
    ui->employe_wid->setCurrentIndex(0);
}




void MainWindow::on_export_2_clicked()
{

    QSqlQueryModel model;
        model.setQuery("SELECT * FROM produit");
        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        QTextDocument doc;
        QTextCursor cursor(&doc);
        QTextCharFormat headerFormat;
        headerFormat.setFontPointSize(15);
        headerFormat.setFontWeight(QFont::Bold);
        cursor.setCharFormat(headerFormat);
        cursor.insertText("Product List\n\n");
        QTextTableFormat tableFormat;
        tableFormat.setAlignment(Qt::AlignLeft);
        QTextTable *table = cursor.insertTable(1, 10, tableFormat);  // 10 columns
        QTextCursor cellCursor;
        for (int col = 0; col < 6; ++col) {
            cellCursor = table->cellAt(0, col).firstCursorPosition();
            cellCursor.insertText(model.headerData(col, Qt::Horizontal).toString());
        }
        for (int row = 0; row < model.rowCount(); ++row) {
            table->appendRows(1);
                cellCursor = table->cellAt(row+1 ,0).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 0)).toString());
                cellCursor = table->cellAt(row + 1,1).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 1)).toString());
                cellCursor = table->cellAt(row + 1,2).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 2)).toString());
                cellCursor = table->cellAt(row + 1,3).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 3)).toString());
                cellCursor = table->cellAt(row + 1,4).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 4)).toString());
                cellCursor = table->cellAt(row + 1,5).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 5)).toString());

        }
        doc.print(&printer);
}



void MainWindow::on_pushButton_4_clicked()
{
    ui->employe_wid->setCurrentIndex(3);
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->employe_wid->setCurrentIndex(4);
}










void MainWindow::on_pushButton_5_clicked()
{
   ui->employe_wid->setCurrentIndex(0);
}


void MainWindow::on_pushButton_toggled(bool checked)
{
   qInfo()<<checked;
}

void MainWindow::on_pushButton_clicked()
{

     ui->employe_wid->setCurrentIndex(2);

}

void MainWindow::on_statis_bar_clicked()
{
    E.state_bar++;
    if(E.state_bar>1)
        E.state_bar=0;
    qInfo()<<E.state_bar;
    if(E.state_bar==1){
        ui->statis_2->setVisible(true);
        ui->list_butt_3->setEnabled(true);

    }
    else
       { ui->statis_2->setVisible(false);
  }
}

void MainWindow::on_list_butt_3_clicked()
{
    ui->employe_wid->setCurrentIndex(0);
}

void MainWindow::on_statis_butt_2_clicked()
{
     ui->employe_wid->setCurrentIndex(4);
}

void MainWindow::on_test_clicked()
{
    qInfo()<<ui->employe_wid->currentIndex();
}



void MainWindow::on_statis_butt_3_clicked()
{
    ui->employe_wid->setCurrentIndex(4);
}

void MainWindow::on_list_butt_4_clicked()
{
    ui->employe_wid->setCurrentIndex(0);
}

void MainWindow::on_statis_bar_2_clicked()
{
    E.state_bar++;
    if(E.state_bar>1)
        E.state_bar=0;
    if(E.state_bar==1){
        ui->list_butt_3->setEnabled(true);
    }
    else
       {
    ui->list_butt_3->setEnabled(false);

    }
}




void MainWindow::on_quit_clicked()
{
    MainWindow::close();
}






void MainWindow::on_return_2_clicked()
{
    ui->employe_wid->setCurrentIndex(6);
}

void MainWindow::on_toggle_statis_clicked()
{
    E.state_bar++;
    if(E.state_bar>1)
        E.state_bar=0;
    qInfo()<<E.state_bar;
    if(E.state_bar==1){
        ui->statis->setVisible(true);
        ui->pushButton->setEnabled(true);
    }
    else {
        ui->statis->setVisible(false);
        ui->pushButton->setEnabled(false);
    }


}

void MainWindow::on_notif_button_clicked()
{


    NotificationParams params;
    for (int i = 0; i < E.get_product_number(); ++i) {
    params.title = E.list_product_notif().at(i);
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    notificationLayout.AddNotificationWidget(this, params);}

}

void MainWindow::on_Delete_button_c_clicked()
{
    ui->delete_conf_c->setVisible(true);
    ui->delete_ok_c->setEnabled(true);
    ui->cancel_delt_c->setEnabled(true);
    ui->delete_ok_c->setVisible(true);
}

void MainWindow::on_cancel_delt_c_clicked()
{
    ui->delete_conf_c->setVisible(false);
    ui->delete_ok_c->setEnabled(false);
    ui->cancel_delt_c->setEnabled(false);
}

void MainWindow::on_delete_ok_c_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
      client em;
       model->setQuery("select * from client");
       ui->delete_ok_c->setVisible(false);
       ui->cancel_delt_c->setEnabled(false);
       ui->delete_conf_c->setVisible(false);
    QModelIndex index = ui->tableView_c->selectionModel()->currentIndex();
    QVariant data = model->data(index, Qt::DisplayRole);
    QString deleted_data=data.toString();
    em.delete_product(deleted_data);
    ui->tableView_c->setModel(C.afficher("",0));
    index=QModelIndex();
}

void MainWindow::on_modify_button_c_clicked()
{
    C.set_mode_add(2);

    client em;
    QString dateString = ui->date_c->text();
    QDate date = QDate::fromString(dateString, "M/d/yyyy");

    if(C.get_mode_add()==2){
    em.set_id(ui->ID_c->text());
    em.set_name(ui->name_c->text());
    em.setLast_name_c(ui->last_name_c->text());
    em.setTel_c(ui->number_c->text());
    em.setMail_c(ui->mail_c->text());
    em.setType_c(ui->type_c_c->text());
    em.setDate_c(date);
    em.setNb_produit(ui->nb_prod->text());
        bool test=em.update_client();

           }


     if(C.get_mode_add()==1){
        C.set_id(ui->ID_c->text());
        C.set_name(ui->name_c->text());
        C.setLast_name_c(ui->last_name_c->text());
        C.setTel_c(ui->number_c->text());
        C.setMail_c(ui->mail_c->text());
        C.setType_c(ui->type_c_c->text());
        C.setDate_c(date);
        C.setNb_produit(ui->nb_prod->text());

        C.add_client();


        int test=C.get_if_client_added();

            if(test==1 )
            {

                ui->cancel_delt_2_c->setVisible(true);
                ui->cancel_delt_2_c->setEnabled(true);
                ui->delete_ok_2_c->setVisible(true);
                ui->delete_ok_2_c->setEnabled(true);

            }


        if(test==0 ){

        ui->cancel_delt_2_c->setVisible(true);
        ui->cancel_delt_2_c->setEnabled(true);
        ui->delete_ok_2_c->setVisible(true);
        ui->delete_ok_2_c->setEnabled(true);}





    }

    ui->tableView_c->setModel(C.afficher("",0));
}



void MainWindow::on_add_emp_c_clicked()
{
    ui->ID_c->setReadOnly(false);
    C.set_mode_add(1);
    ui->client_wid->setCurrentIndex(1);
    ui->ID_c->setText("");
    ui->name_c->setText("");
    ui->last_name_c->setText("");
    ui->number_c->setText("");
    ui->mail_c->setText("");
    ui->type_c_c->setText("");
}

void MainWindow::on_return_to_list_c_clicked()
{

    ui->client_wid->setCurrentIndex(0);

}

void MainWindow::on_add_employe_c_clicked()
{
    C.set_mode_add(1);

    client em;
    QString dateString = ui->date_c->text();
    QDate date = QDate::fromString(dateString, "M/d/yyyy");

    if(C.get_mode_add()==2){
    em.set_id(ui->ID_c->text());
    em.set_name(ui->name_c->text());
    em.setLast_name_c(ui->last_name_c->text());
    em.setTel_c(ui->number_c->text());
    em.setMail_c(ui->mail_c->text());
    em.setType_c(ui->type_c_c->text());
    em.setDate_c(date);
    em.setNb_produit(ui->nb_prod->text());
        bool test=em.update_client();

           }


     if(C.get_mode_add()==1){
        C.set_id(ui->ID_c->text());
        C.set_name(ui->name_c->text());
        C.setLast_name_c(ui->last_name_c->text());
        C.setTel_c(ui->number_c->text());
        C.setMail_c(ui->mail_c->text());
        C.setType_c(ui->type_c_c->text());
        C.setDate_c(date);
        C.setNb_produit(ui->nb_prod->text());

        C.add_client();


        int test=C.get_if_client_added();

            if(test==1 )
            {

                ui->cancel_delt_2_c->setVisible(true);
                ui->cancel_delt_2_c->setEnabled(true);
                ui->delete_ok_2_c->setVisible(true);
                ui->delete_ok_2_c->setEnabled(true);

            }


        if(test==0 ){

        ui->cancel_delt_2_c->setVisible(true);
        ui->cancel_delt_2_c->setEnabled(true);
        ui->delete_ok_2_c->setVisible(true);
        ui->delete_ok_2_c->setEnabled(true);}





    }

    ui->tableView_c->setModel(C.afficher("",0));
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->employe_wid->setCurrentIndex(3);
}

void MainWindow::on_refresh_emp_c_clicked()
{
    QString name;
    QString mail;
    QString number;
    QString type;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->clear();
    model->setQuery("select * from client");
    QModelIndex index = ui->tableView_c->selectionModel()->currentIndex();
    qInfo()<<index;
     if (index.isValid()) {
    QModelIndex columnIndex = model->index(index.row(), 1);
    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 4);
    data = model->data(columnIndex, Qt::DisplayRole);
    mail=data.toString();
    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    number=data.toString();
    columnIndex = model->index(index.row(), 5);
    data = model->data(columnIndex, Qt::DisplayRole);
    type=data.toString();

     }

}

void MainWindow::on_search_butt_c_clicked()
{
    QString data;
    data=ui->search_c->text();
    if(data=="")
            C.set_view_mode(0);
     else
            C.set_view_mode(1);
    ui->tableView_c->setModel(C.afficher(data,C.get_view_mode()));
}

void MainWindow::on_pushButton_c_clicked()
{
    ui->client_wid->setCurrentIndex(2);
    ui->statis_bar_c->setEnabled(true);
    ui->list_butt_3_c->setEnabled(true);

}

void MainWindow::on_toggle_statis_c_clicked()
{
    C.state_bar++;
    if(C.state_bar>1)
        C.state_bar=0;
    qInfo()<<C.state_bar;
    if(C.state_bar==1){
        ui->statis_c->setVisible(true);
        ui->pushButton_c->setEnabled(true);
    }
    else {
        ui->statis_c->setVisible(false);
        ui->pushButton_c->setEnabled(false);
    }
}

void MainWindow::on_statis_bar_c_clicked()
{
    C.state_bar++;
    if(C.state_bar>1)
        C.state_bar=0;
    qInfo()<<C.state_bar;
    if(C.state_bar==1){
        ui->statis_2_c->setVisible(true);
        ui->list_butt_3_c->setEnabled(true);

    }
    else
       { ui->statis_2_c->setVisible(false);
  }
}

void MainWindow::on_list_butt_3_c_clicked()
{
    ui->client_wid->setCurrentIndex(0);

}

void MainWindow::on_pushButton_3_clicked()
{
    ui->employe_wid->setCurrentIndex(0);
}

void MainWindow::on_delete_ok_2_c_clicked()
{

    ui->cancel_delt_2_c->setVisible(false);
    ui->cancel_delt_2_c->setEnabled(false);
    ui->delete_ok_2_c->setVisible(false);
    ui->delete_ok_2_c->setEnabled(false);
    ui->client_wid->setCurrentIndex(0);
}

void MainWindow::on_cancel_delt_2_c_clicked()
{

    ui->cancel_delt_2_c->setVisible(false);
    ui->cancel_delt_2_c->setEnabled(false);
    ui->delete_ok_2_c->setVisible(false);
    ui->delete_ok_2_c->setEnabled(false);
}

void MainWindow::on_export_2_c_clicked()
{
    QSqlQueryModel model;
        model.setQuery("SELECT * FROM client");
        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        QTextDocument doc;
        QTextCursor cursor(&doc);
        QTextCharFormat headerFormat;
        headerFormat.setFontPointSize(15);
        headerFormat.setFontWeight(QFont::Bold);
        cursor.setCharFormat(headerFormat);
        cursor.insertText("client List\n\n");
        QTextTableFormat tableFormat;
        tableFormat.setAlignment(Qt::AlignLeft);
        QTextTable *table = cursor.insertTable(1, 10, tableFormat);  // 10 columns
        QTextCursor cellCursor;
        for (int col = 0; col < 7; ++col) {
            cellCursor = table->cellAt(0, col).firstCursorPosition();
            cellCursor.insertText(model.headerData(col, Qt::Horizontal).toString());
        }
        for (int row = 0; row < model.rowCount(); ++row) {
            table->appendRows(1);
                cellCursor = table->cellAt(row+1 ,0).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 0)).toString());
                cellCursor = table->cellAt(row + 1,1).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 1)).toString());
                cellCursor = table->cellAt(row + 1,2).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 2)).toString());
                cellCursor = table->cellAt(row + 1,3).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 3)).toString());
                cellCursor = table->cellAt(row + 1,4).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 4)).toString());
                cellCursor = table->cellAt(row + 1,5).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 5)).toString());
                cellCursor = table->cellAt(row + 1,6).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 6)).toString());

        }
        doc.print(&printer);
}

void MainWindow::on_claim_clicked()
{
    ui->client_wid->setCurrentIndex(3);
}

void MainWindow::on_return_client_clicked()
{
    ui->client_wid->setCurrentIndex(0);
}

void MainWindow::on_submit_clicked()
{
    Smtp* smtp = new Smtp("hnachamine@gmail.com","nxem iunr dsyv vmvy", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    qInfo()<<"size of mails"<< E.list_mail_fournisseur().size();

    for (int i = 0; i < E.list_mail_fournisseur().size(); ++i) {
           QString email = E.list_mail_fournisseur().at(i);
           smtp->sendMail("hnachamine@gmail.com", email, "",ui->claim_form->text());
           qInfo()<<"mails"<<E.list_mail_fournisseur().at(i);
       }
    disconnect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
}

void MainWindow::on_refresh_emp_f_clicked()
{
    QString name;
    QString mail;
    QString number;
    QString type;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->clear();
    model->setQuery("select * from fournisseur");
    QModelIndex index = ui->tableView_f->selectionModel()->currentIndex();
    qInfo()<<index;
     if (index.isValid()) {
    QModelIndex columnIndex = model->index(index.row(), 1);
    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 4);
    data = model->data(columnIndex, Qt::DisplayRole);
    mail=data.toString();
    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    number=data.toString();
    columnIndex = model->index(index.row(), 5);
    data = model->data(columnIndex, Qt::DisplayRole);
    type=data.toString();

     }
     ui->name_label_f->setText(name);
     ui->number_f->setText(number);
      ui->type->setText(type);
}

void MainWindow::on_Delete_button_f_clicked()
{
    ui->delete_conf_f->setVisible(true);
    ui->delete_ok_f->setEnabled(true);
    ui->cancel_delt_f->setEnabled(true);
    ui->delete_ok_f->setVisible(true);
}

void MainWindow::on_delete_ok_f_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
      fournisseur em;
       model->setQuery("select * from fournisseur");
       ui->delete_ok_f->setVisible(false);
       ui->cancel_delt_f->setEnabled(false);
       ui->delete_conf_f->setVisible(false);
    QModelIndex index = ui->tableView_f->selectionModel()->currentIndex();
    QVariant data = model->data(index, Qt::DisplayRole);
    QString deleted_data=data.toString();
    em.delete_fournisseur(deleted_data);
    ui->tableView_f->setModel(F.afficher("",0));
    index=QModelIndex();
}

void MainWindow::on_cancel_delt_f_clicked()
{
    ui->delete_conf_f->setVisible(false);
    ui->delete_ok_f->setEnabled(false);
    ui->cancel_delt_f->setEnabled(false);
}

void MainWindow::on_add_emp_f_clicked()
{
    ui->ID_f->setReadOnly(false);
    F.set_mode_add(1);
    ui->fournisseur_wid->setCurrentIndex(1);
    ui->ID_f->setText("");
    ui->name_f->setText("");
    ui->adress_f->setText("");
    ui->number_f_2->setText("");
    ui->mail_f_2->setText("");
    ui->type_pf_f->setText("");

}

void MainWindow::on_return_to_list_f_clicked()
{

    ui->fournisseur_wid->setCurrentIndex(0);


}

void MainWindow::on_add_employe_f_clicked()
{    F.set_mode_add(1);
    fournisseur em;
    QString dateString = ui->date_collab_f->text();
    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");

    if(F.get_mode_add()==2){
    em.set_id(ui->ID_f->text());
    em.set_name(ui->name_f->text());
    em.setAdresse_f(ui->adress_f->text());
    em.setTel_f(ui->number_f_2->text());
    em.setMail_f(ui->mail_f_2->text());
    em.setType_pf(ui->type_pf_f->text());
    em.setDate_collab(date);
        bool test=em.update_fournisseur();

           }


     if(F.get_mode_add()==1){
        F.set_id(ui->ID_f->text());
        F.set_name(ui->name_f->text());
        F.setAdresse_f(ui->adress_f->text());
        F.setTel_f(ui->number_f_2->text());
        F.setMail_f(ui->mail_f_2->text());
        F.setType_pf(ui->type_pf_f->text());
        F.setDate_collab(date);

        F.add_fournisseur();


        int test=F.get_if_fournisseur_added();

            if(test==1 )
            {


            }


        if(test==0 ){
    }





    }

    ui->tableView_f->setModel(F.afficher("",0));
}



void MainWindow::on_delete_ok__f_clicked()
{
    ui->fournisseur_wid->setCurrentIndex(0);
}

void MainWindow::on_cancel_delt_f_2_clicked()
{
}

void MainWindow::on_fournisseur_clicked()
{
    ui->employe_wid->setCurrentIndex(4);
}

void MainWindow::on_export_f_clicked()
{
    QSqlQueryModel model;
        model.setQuery("SELECT * FROM fournisseur");
        QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        QTextDocument doc;
        QTextCursor cursor(&doc);
        QTextCharFormat headerFormat;
        headerFormat.setFontPointSize(15);
        headerFormat.setFontWeight(QFont::Bold);
        cursor.setCharFormat(headerFormat);
        cursor.insertText("fournisseur List\n\n");
        QTextTableFormat tableFormat;
        tableFormat.setAlignment(Qt::AlignLeft);
        QTextTable *table = cursor.insertTable(1, 10, tableFormat);  // 10 columns
        QTextCursor cellCursor;
        for (int col = 0; col < 7; ++col) {
            cellCursor = table->cellAt(0, col).firstCursorPosition();
            cellCursor.insertText(model.headerData(col, Qt::Horizontal).toString());
        }
        for (int row = 0; row < model.rowCount(); ++row) {
            table->appendRows(1);
                cellCursor = table->cellAt(row+1 ,0).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 0)).toString());
                cellCursor = table->cellAt(row + 1,1).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 1)).toString());
                cellCursor = table->cellAt(row + 1,2).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 2)).toString());
                cellCursor = table->cellAt(row + 1,3).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 3)).toString());
                cellCursor = table->cellAt(row + 1,4).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 4)).toString());
                cellCursor = table->cellAt(row + 1,5).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 5)).toString());
                cellCursor = table->cellAt(row + 1,6).firstCursorPosition();
                cellCursor.insertText(model.data(model.index(row, 6)).toString());

        }
        doc.print(&printer);
}

void MainWindow::on_search_butt_2_clicked()
{
    QString data;
    data=ui->search_f->text();
    if(data=="")
            F.set_view_mode(0);
     else
            F.set_view_mode(1);
    ui->tableView_f->setModel(F.afficher(data,F.get_view_mode()));
}

void MainWindow::on_toggle_statis_f_clicked()
{
    F.state_bar++;
    if(F.state_bar>1)
        F.state_bar=0;
    qInfo()<<F.state_bar;
    if(F.state_bar==1){
        ui->statis_f->setVisible(true);
        ui->pushButton_f->setEnabled(true);
    }
    else {
        ui->statis_f->setVisible(false);
        ui->pushButton_f->setEnabled(false);
    }
}

void MainWindow::on_pushButton_f_clicked()
{
    ui->fournisseur_wid->setCurrentIndex(2);

}

void MainWindow::on_statis_bar_f_clicked()
{
    F.state_bar++;
    if(F.state_bar>1)
        F.state_bar=0;
    qInfo()<<F.state_bar;
    if(F.state_bar==1){
        ui->statis_f_2->setVisible(true);
        ui->list_butt_f->setEnabled(true);

    }
    else
       { ui->statis_f_2->setVisible(false);
  }
}

void MainWindow::on_list_butt_f_clicked()
{
    ui->fournisseur_wid->setCurrentIndex(0);
}

void MainWindow::on_modify_button_f_clicked()
{
    F.set_mode_add(2);
       fournisseur em;
       QString dateString = ui->date_collab_f->text();
       QDate date = QDate::fromString(dateString, "M/d/yyyy");

       if(F.get_mode_add()==2){
       em.set_id(ui->ID_f->text());
       em.set_name(ui->name_f->text());
       em.setAdresse_f(ui->adress_f->text());
       em.setTel_f(ui->number_f_2->text());
       em.setMail_f(ui->mail_f_2->text());
       em.setType_pf(ui->type_pf_f->text());
       em.setDate_collab(date);
           bool test=em.update_fournisseur();

              }


        if(F.get_mode_add()==1){
           F.set_id(ui->ID_f->text());
           F.set_name(ui->name_f->text());
           F.setAdresse_f(ui->adress_f->text());
           F.setTel_f(ui->number_f_2->text());
           F.setMail_f(ui->mail_f_2->text());
           F.setType_pf(ui->type_pf_f->text());
           F.setDate_collab(date);

           F.add_fournisseur();


           int test=F.get_if_fournisseur_added();

               if(test==1 )
               {


               }


           if(test==0 ){
       }





       }

       ui->tableView_f->setModel(F.afficher("",0));
}


void MainWindow::on_p_m_clicked()
{
    QModelIndex index = ui->tableView_c->selectionModel()->currentIndex();
    if (!index.isValid()) {
        qDebug() << "No row is currently selected.";
        return;
    }
    QAbstractItemModel* model = ui->tableView_c->model();
    if (!model) {
        qDebug() << "The model is not set for the table view.";
        return;
    }
    int columnIndex = 7;
    QVariant data = model->data(model->index(index.row(), columnIndex), Qt::DisplayRole);
    if (!data.isValid()) {
        qDebug() << "No data found in column" << columnIndex;
        return;
    }    int temp;
    temp=data.toInt()*50;
    qDebug() <<temp;
    ui->num_pm->setText(QString::number(temp));
}

void MainWindow::on_emp_pic_c_linkActivated(const QString &link)
{

}

void MainWindow::on_generate_qrcode_clicked()
{
QString name,tel,temp;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from fournisseur");
    QModelIndex index = ui->tableView_f->selectionModel()->currentIndex();
     QModelIndex columnIndex = model->index(index.row(), 0);
    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    columnIndex = model->index(index.row(), 1);
    data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    tel=data.toString();

    temp="name:"+name+" tel:"+tel;


    int levelIndex = 1;
    int versionIndex = 0;
    bool bExtent = true;
    int maskIndex = -1;
    QString encodeString =temp;

    successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
    if ( !successfulEncoding )
    {
        ui->qr_image->clear();
        ui->qr_image->setText( tr("QR Code...") );
                return;
    }

    int qrImageSize = qrEncode.m_nSymbleSize;
    encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
    QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
    encodeImage.fill( 1 );
    for ( int i = 0; i < qrImageSize; i++ )
        for ( int j = 0; j < qrImageSize; j++ )
            if ( qrEncode.m_byModuleData[i][j] )
                encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

    ui->qr_image->setPixmap( QPixmap::fromImage( encodeImage ) );
    int scale_size = encodeImageSize * 4;

    const QPixmap & scale_image = ui->qr_image->pixmap().scaled( scale_size, scale_size );
    ui->qr_image->setPixmap( scale_image );

}

void MainWindow::readarduino()
{

    int lastIndex;
    QString serialBuffer;
    //QByteArray tosd = QByteArray::number(valueToSend) + '\n';

    QByteArray data = serialPort->readAll();
    serialBuffer += QString::fromUtf8(data);
    QStringList lines = serialBuffer.split('\n', Qt::SkipEmptyParts);

    if (!lines.isEmpty()) {
        serialBuffer = "";
        QString lastLine = lines.last();
        if (lastLine.startsWith("Received:")) {
            lastLine = lastLine.mid(9).trimmed();
        }
        bool conversionOk;
        lastIndex = lastLine.toInt(&conversionOk);
        if (conversionOk) {
            qDebug() << "---------------->" << lastIndex;
        } else {
            qDebug() << "Conversion failed for line:" << lastLine;
        }
    } else {
        qDebug() << "No complete lines received yet.";
    }
    if(toggle_ard==1)
    ui->quantity->setText(QString::number(lastIndex));






}

void MainWindow::on_pushButton_7_clicked()
{

     toggle_ard++;
     if(toggle_ard>1)
         toggle_ard =0;

     if(toggle_ard==1)
         ui->pushButton_7->setText("arduino");
     if(toggle_ard==0)
         ui->pushButton_7->setText("manually");

}


void MainWindow::on_modify_button_2_clicked()
{
    E.set_mode_add(2);
    produit em;
    QString dateString = ui->date_a_label->text();
    QDate date = QDate::fromString(dateString, "dd/MM/yyyy");
    QString dateString2 = ui->date_e_label->text();
    QDate date2 = QDate::fromString(dateString2, "dd/MM/yyyy");

    if(E.get_mode_add()==2){
    em.set_id(ui->ID->text());
    em.set_name(ui->name->text());
    em.setPrix_u(ui->price->text().toUInt());
    em.setQuantite_p(ui->quantity->text().toUInt());
    em.setDate_a(date);
    em.setDate_e(date2);
        bool test=em.update_product();

           }


     if(E.get_mode_add()==1){
        E.set_id(ui->ID->text());
        E.set_name(ui->name->text());
        E.setPrix_u(ui->price->text().toUInt());
        E.setQuantite_p(ui->quantity->text().toUInt());
        E.setDate_a(date);
        E.setDate_e(date2);

        E.add_product();


        int test=E.get_if_emp_added();

            if(test==1 )
            {
                ui->unable_to_add->setVisible(true);
                ui->unable_to_add->setEnabled(true);
                ui->cancel_delt_2->setVisible(true);
                ui->cancel_delt_2->setEnabled(true);
                ui->delete_ok_2->setVisible(true);
                ui->delete_ok_2->setEnabled(true);
                 qInfo()<<E.getPrix_u();
                  qInfo()<<dateString;

            }


        if(test==0 ){
        ui->unable_to_add->setVisible(true);
        ui->unable_to_add->setEnabled(true);
        ui->cancel_delt_2->setVisible(true);
        ui->cancel_delt_2->setEnabled(true);
        ui->delete_ok_2->setVisible(true);
        ui->delete_ok_2->setEnabled(true);}





    }

    ui->tableView->setModel(E.afficher("",0));

}


void MainWindow::on_modify_button_c_5_clicked()
{
    QString id;
    QString name;
    QString last_name;
    QString number;
    QString mail;
    QString type_c;
    QDate date_c;

    client em;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from client");
    C.set_mode_add(2);
    QModelIndex index = ui->tableView_c->selectionModel()->currentIndex();
     QModelIndex columnIndex = model->index(index.row(), 0);
     if (index.isValid()) {
    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    id=data.toString();
    ui->ID_c->setText(id);
    columnIndex = model->index(index.row(), 1);
    data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 2);
    data = model->data(columnIndex, Qt::DisplayRole);
    last_name=data.toString();

    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    number=data.toString();

    columnIndex = model->index(index.row(), 4);
    data = model->data(columnIndex, Qt::DisplayRole);
    mail=data.toString();


    columnIndex = model->index(index.row(), 5);
    data = model->data(columnIndex, Qt::DisplayRole);
    type_c=data.toString();

    columnIndex = model->index(index.row(), 6);
    data = model->data(columnIndex, Qt::DisplayRole);
    date_c=data.toDate();

     ui->ID_c->setReadOnly(true);
     ui->name_c->setText(name);
     ui->last_name_c->setText(last_name);
     ui->number_c->setText(number);
     ui->mail_c->setText(mail);
     ui->type_c_c->setText(type_c);
     ui->date_c->setDate(date_c);
}
}


void MainWindow::on_modify_button_f_2_clicked()
{
    QString id;
    QString name;
    QString adress;
    QString number;
    QString mail;
    QString type_pf;
    QDate date_collab;

    fournisseur em;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from fournisseur");
    F.set_mode_add(2);
    QModelIndex index = ui->tableView_f->selectionModel()->currentIndex();
     QModelIndex columnIndex = model->index(index.row(), 0);
     if (index.isValid()) {

    QVariant data = model->data(columnIndex, Qt::DisplayRole);
    id=data.toString();
    ui->ID_f->setText(id);
    columnIndex = model->index(index.row(), 1);
    data = model->data(columnIndex, Qt::DisplayRole);
    name=data.toString();
    columnIndex = model->index(index.row(), 2);
    data = model->data(columnIndex, Qt::DisplayRole);
    adress=data.toString();

    columnIndex = model->index(index.row(), 3);
    data = model->data(columnIndex, Qt::DisplayRole);
    number=data.toString();

    columnIndex = model->index(index.row(), 4);
    data = model->data(columnIndex, Qt::DisplayRole);
    mail=data.toString();


    columnIndex = model->index(index.row(), 5);
    data = model->data(columnIndex, Qt::DisplayRole);
    type_pf=data.toString();

    columnIndex = model->index(index.row(), 6);
    data = model->data(columnIndex, Qt::DisplayRole);
    date_collab=data.toDate();

     ui->ID_f->setReadOnly(true);
     ui->name_f->setText(name);
     ui->adress_f->setText(adress);
     ui->number_f_2->setText(number);
     ui->mail_f_2->setText(mail);
     ui->type_pf_f->setText(type_pf);
     ui->date_collab_f->setDate(date_collab);
}
}


