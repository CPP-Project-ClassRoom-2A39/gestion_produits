#include "fournisseur.h"
#include<QDebug>
fournisseur::fournisseur()
{
    id_f="";
    name_f="";
    adresse_f="";
    tel_f="";
    mail_f="";
    type_pf="";
    mod_add=0;
    table_mod=0;

     state_bar=0;

}
fournisseur::fournisseur(QString id,QString name,QString tel_f,QString mail_f,QString type_pf,QString adresse_f,QDate date_collab)
{
    this->id_f=id;
    this->name_f=name;
    this->adresse_f=adresse_f;
    this->tel_f=tel_f;
    this->mail_f=mail_f;
    this->type_pf=type_pf;
    this->date_collab=date_collab;
    this->mod_add=mod_add;

}
void fournisseur:: set_id(QString id){this->id_f=id;}
QString fournisseur:: get_id(){return id_f;}
void fournisseur:: set_name(QString name){this->name_f=name;}
QString fournisseur:: get_name(){return name_f;}




int fournisseur::get_mode_add(){return mod_add;}
void fournisseur::set_mode_add(int value){this->mod_add=value;}
QSqlQueryModel* fournisseur::afficher(QString data,int mode)
{

    QSqlQueryModel* model=new QSqlQueryModel();
      if(mode==0)
       model->setQuery("select * from fournisseur order by name_f");
       if(mode==1)
       {
           model->setQuery("select * from client where id_f like '" + data + "%'");
       }

       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("id_fournisseur"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("name_fournisseur"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Adress"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Number"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("Mail"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("Type"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("Date_collab"));




    return model;
}
void fournisseur::add_fournisseur()
{
    QString query;
    QSqlQuery qry;
    qry.prepare("INSERT INTO fournisseur (id_f, name_f, adress_f, tel_f, mail_f, type_pf,date_collab)""VALUES (:id_f,:name_f,:adress_f,:tel_f,:mail_f,:type_pf,:date_collab)");

    qry.bindValue(":id_f",get_id());
    qry.bindValue(":name_f",get_name());
    qry.bindValue(":adress_f",getAdresse_f());
    qry.bindValue(":tel_f",getTel_f());
    qry.bindValue(":mail_f",getMail_f());
    qry.bindValue(":type_pf",getType_pf());
    qry.bindValue(":date_collab",getDate_collab());
    if(qry.exec())
       added_not_added=1;
    else
      added_not_added=0;
qInfo()<<added_not_added;
}
void fournisseur::delete_fournisseur(QString data)
{
    QString query;
    QSqlQuery qry;
    qry.prepare("DELETE FROM fournisseur where id_f=:value");
    qry.bindValue(":value",data);
    qry.exec();
}

bool fournisseur::update_fournisseur() {
    QSqlQuery qry;
    qry.prepare("UPDATE fournisseur SET id_f = :id_f, "
                "name_f = :name_f, "
                "adress_f = :adress_f, "
                "tel_f = :tel_f, "
                "mail_f = :mail_f, "
                "type_pf = :type_pf, "
                "date_collab = :date_collab "
                "WHERE id_f = :user_name");

    qry.bindValue(":id_f", id_f);
    qry.bindValue(":name_f", get_name());
    qry.bindValue(":adress_f", getAdresse_f());
    qry.bindValue(":tel_f", getTel_f());
    qry.bindValue(":mail_f", getMail_f());
    qry.bindValue(":type_pf", getType_pf());
    qry.bindValue(":date_collab", getDate_collab());
    qry.bindValue(":user_name", id_f);

    return qry.exec();
}


void fournisseur::set_view_mode(int data)
{
    this->table_mod=data;
}
int fournisseur::get_view_mode()
{
    return  table_mod;
}
int fournisseur::get_if_fournisseur_added()
{
    return added_not_added;
}

QString fournisseur::getTel_f() const
{
    return tel_f;
}

void fournisseur::setTel_f(const QString &value)
{
    tel_f = value;
}

QString fournisseur::getMail_f() const
{
    return mail_f;
}

void fournisseur::setMail_f(const QString &value)
{
    mail_f = value;
}

QString fournisseur::getType_pf() const
{
    return type_pf;
}

void fournisseur::setType_pf(const QString &value)
{
    type_pf = value;
}

QString fournisseur::getAdresse_f() const
{
    return adresse_f;
}

void fournisseur::setAdresse_f(const QString &value)
{
    adresse_f = value;
}

QDate fournisseur::getDate_collab() const
{
    return date_collab;
}

void fournisseur::setDate_collab(const QDate &value)
{
    date_collab = value;
}






