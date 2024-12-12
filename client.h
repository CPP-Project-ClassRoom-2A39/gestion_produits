#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <QDate>

class client
{
public:
    client();
    client(QString id,QString name,QString last_name_c,QString tel_c,QString mail_c,QString type_c,QDate date_c);
    void set_id(QString id_c);
    QString get_id();
    void set_name(QString name_c);
    QString get_name();


    QSqlQueryModel* afficher(QString data,int mode);
    void delete_product(QString data);


    int get_mode_add();
    void set_mode_add(int value);   
    void add_client();
    bool  update_client();
    void set_view_mode(int data);
    int get_view_mode();
    int get_if_client_added();



    int emp_add;



    QString return_name(QString id_c);
    QString return_quantity(int id_c);
    int state_bar;



    QString getLast_name_c() const;
    void setLast_name_c(const QString &value);

    QString getTel_c() const;
    void setTel_c(const QString &value);

    QString getMail_c() const;
    void setMail_c(const QString &value);

    QString getType_c() const;
    void setType_c(const QString &value);

    QDate getDate_c() const;
    void setDate_c(const QDate &value);



    QString getNb_produit() const;
    void setNb_produit(const QString &value);

private:
    QString id_c,name_c,last_name_c,tel_c,mail_c,type_c,nb_produit;
    QDate date_c;

    int mod_add;
    int table_mod;
    int added_not_added;
    QString rating;

};

#endif
