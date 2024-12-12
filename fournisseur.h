#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <QDate>

class fournisseur
{
public:
    fournisseur();
    fournisseur(QString id,QString name,QString tel_f,QString mail_f,QString type_pf,QString adresse_f,QDate date_collab);
    void set_id(QString id_f);
    QString get_id();
    void set_name(QString name_f);
    QString get_name();


    QSqlQueryModel* afficher(QString data,int mode);
    void delete_fournisseur(QString data);


    int get_mode_add();
    void set_mode_add(int value);   
    void add_fournisseur();
    bool  update_fournisseur();
    void set_view_mode(int data);
    int get_view_mode();
    int get_if_fournisseur_added();



    int emp_add;



    QString return_name(QString id_f);
    QString return_quantity(int id_f);
    int state_bar;





    QString getTel_f() const;
    void setTel_f(const QString &value);

    QString getMail_f() const;
    void setMail_f(const QString &value);

    QString getType_pf() const;
    void setType_pf(const QString &value);

    QString getAdresse_f() const;
    void setAdresse_f(const QString &value);

    QDate getDate_collab() const;
    void setDate_collab(const QDate &value);

private:
    QString id_f,name_f,tel_f,mail_f,type_pf,adresse_f;
    QDate date_collab;

    int mod_add;
    int table_mod;
    int added_not_added;
    QString rating;

};

#endif
