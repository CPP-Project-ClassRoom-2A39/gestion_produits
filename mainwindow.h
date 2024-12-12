
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<stdio.h>
#include<QObject>
#include <QMainWindow>
#include"produit.h"
#include"client.h"
#include"fournisseur.h"
#include <QLabel>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QtCore>
#include<QtGui>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QVector>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include"smtp.h"
#include"QRCodeGenerator.h"
#include "Notifications/NotificationLayout.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 public slots:
void readarduino();

private slots:

    void on_Delete_button_clicked();

    void set_stars(QString data);

    void on_delete_ok_clicked();

    void on_cancel_delt_clicked();

    void on_modify_button_clicked();

    void on_return_to_list_clicked();

    void on_add_employe_clicked();

    void on_add_emp_clicked();

    void sendmailtoallfournisseur(const QString& text);




    void on_return_to_list_2_clicked();


    void on_search_butt_clicked();

    void on_refresh_emp_clicked();



    void on_statis_butt_clicked();

    void on_list_butt_2_clicked();

    void on_cancel_delt_2_clicked();

    void on_delete_ok_2_clicked();





    void on_export_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();









    void on_pushButton_5_clicked();

    void on_list_butt_clicked();
    void on_pushButton_toggled(bool checked);

    void on_pushButton_clicked();

    void on_statis_bar_clicked();

    void on_list_butt_3_clicked();

    void on_statis_butt_2_clicked();

    void on_test_clicked();



    void on_statis_butt_3_clicked();

    void on_list_butt_4_clicked();

    void on_statis_bar_2_clicked();



    void on_quit_clicked();



    void on_return_2_clicked();

    void on_toggle_statis_clicked();


    void on_notif_button_clicked();

    void on_Delete_button_c_clicked();

    void on_cancel_delt_c_clicked();

    void on_delete_ok_c_clicked();

    void on_modify_button_c_clicked();

    void on_add_emp_c_clicked();

    void on_return_to_list_c_clicked();

    void on_add_employe_c_clicked();

    void on_pushButton_2_clicked();

    void on_refresh_emp_c_clicked();

    void on_search_butt_c_clicked();

    void on_pushButton_c_clicked();

    void on_toggle_statis_c_clicked();

    void on_statis_bar_c_clicked();

    void on_list_butt_3_c_clicked();

    void on_pushButton_3_clicked();

    void on_delete_ok_2_c_clicked();

    void on_cancel_delt_2_c_clicked();

    void on_export_2_c_clicked();

    void on_claim_clicked();

    void on_return_client_clicked();

    void on_submit_clicked();

    void on_refresh_emp_f_clicked();

    void on_Delete_button_f_clicked();

    void on_delete_ok_f_clicked();

    void on_cancel_delt_f_clicked();

    void on_add_emp_f_clicked();

    void on_return_to_list_f_clicked();

    void on_add_employe_f_clicked();

    void on_delete_ok__f_clicked();

    void on_cancel_delt_f_2_clicked();

    void on_fournisseur_clicked();

    void on_export_f_clicked();

    void on_search_butt_2_clicked();

    void on_toggle_statis_f_clicked();

    void on_pushButton_f_clicked();

    void on_statis_bar_f_clicked();

    void on_list_butt_f_clicked();

    void on_modify_button_f_clicked();

    void on_p_m_clicked();

    void on_emp_pic_c_linkActivated(const QString &link);

    void on_generate_qrcode_clicked();

    void on_pushButton_7_clicked();

    void on_modify_button_2_clicked();

    void on_modify_button_c_5_clicked();

    void on_modify_button_f_2_clicked();

private:
    Ui::MainWindow *ui;
     QTimer *timer;
    produit E;
    client C;
    fournisseur F;
    QVector<QLabel*> notif_txt_list;
    QSerialPort *serialPort;
    QByteArray serialData;
    QString serialbuffer;
    QGridLayout *layout;
     QStringList files;
     bool successfulEncoding;
     CQR_Encode qrEncode;
     int encodeImageSize;
     NotificationLayout notificationLayout;
     int toggle_ard;
    /*QMediaPlayer *player;
    QVideoWidget *video;
    qint64 mduration;
    bool is_pause=true;*/
};
#endif // MAINWINDOW_H
