#include "client.h"
#include<QDebug>
client::client()
{
    id_c="";
    name_c="";
    last_name_c="";
    tel_c="";
    mail_c="";
    type_c="";
    mod_add=0;
    table_mod=0;

     state_bar=0;

}
client::client(QString id,QString name,QString last_name_c,QString tel_c,QString mail_c,QString type_c,QDate date_c)
{
    this->id_c=id;
    this->name_c=name;
    this->last_name_c=last_name_c;
    this->tel_c=tel_c;
    this->mail_c=mail_c;
    this->type_c=type_c;
    this->date_c=date_c;
    this->mod_add=mod_add;

}
void client:: set_id(QString id){this->id_c=id;}
QString client:: get_id(){return id_c;}
void client:: set_name(QString name){this->name_c=name;}
QString client:: get_name(){return name_c;}




int client::get_mode_add(){return mod_add;}
void client::set_mode_add(int value){this->mod_add=value;}
QSqlQueryModel* client::afficher(QString data,int mode)
{

    QSqlQueryModel* model=new QSqlQueryModel();
      if(mode==0)
       model->setQuery("select * from client order by nom_c");
       if(mode==1)
       {
           model->setQuery("select * from client where id_c like '" + data + "%'");
       }

       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("id_client"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("name_client"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("last_name_client"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Number"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("Mail"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("Type"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("Date_c"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("nb_product"));




    return model;
}
void client::add_client()
{
    QString query;
    QSqlQuery qry;
    qry.prepare("INSERT INTO client (id_c, nom_c, lastname_c, tel_c, mail_c, type_c, date_c, nb_produit)"
                "VALUES (:id_c, :nom_c, :lastname_c, :tel_c, :mail_c, :type_c, :date_c, :nb_produit)");

    qry.bindValue(":id_c", get_id());
    qry.bindValue(":nom_c", get_name());
    qry.bindValue(":lastname_c", getLast_name_c());
    qry.bindValue(":tel_c", getTel_c());
    qry.bindValue(":mail_c", getMail_c());
    qry.bindValue(":type_c", getType_c());
    qry.bindValue(":date_c", getDate_c());
    qry.bindValue(":nb_produit", getNb_produit());

    if (!qry.exec()) {
        qDebug() << "Error executing query:" ;
    } else {
        qDebug() << "Query executed successfully.";
    }
    if(qry.exec())
       added_not_added=1;
    else
      added_not_added=0;
qInfo()<<added_not_added;
}
void client::delete_product(QString data)
{
    QString query;
    QSqlQuery qry;
    qry.prepare("DELETE FROM client where id_c=:value");
    qry.bindValue(":value",data);
    qry.exec();
}

bool client::update_client() {
    QSqlQuery qry;
    qry.prepare("UPDATE client SET id_c = :id_c, "
                "nom_c = :nom_c, "
                "lastname_c = :lastname_c, "
                "tel_c = :tel_c, "
                "mail_c = :mail_c, "
                "type_c = :type_c, "
                "date_c = :date_c "
                "WHERE id_c = :user_name");

    qry.bindValue(":id_c", id_c);
    qry.bindValue(":nom_c", get_name());
    qry.bindValue(":lastname_c", getLast_name_c());
    qry.bindValue(":tel_c", getTel_c());
    qry.bindValue(":mail_c", getMail_c());
    qry.bindValue(":type_c", getType_c());
    qry.bindValue(":date_c", getDate_c());
    qry.bindValue(":user_name", id_c);

    return qry.exec();
}


void client::set_view_mode(int data)
{
    this->table_mod=data;
}
int client::get_view_mode()
{
    return  table_mod;
}
int client::get_if_client_added()
{
    return added_not_added;
}

QString client::getLast_name_c() const
{
    return last_name_c;
}

void client::setLast_name_c(const QString &value)
{
    last_name_c = value;
}

QString client::getTel_c() const
{
    return tel_c;
}

void client::setTel_c(const QString &value)
{
    tel_c = value;
}

QString client::getMail_c() const
{
    return mail_c;
}

void client::setMail_c(const QString &value)
{
    mail_c = value;
}

QString client::getType_c() const
{
    return type_c;
}

void client::setType_c(const QString &value)
{
    type_c = value;
}

QDate client::getDate_c() const
{
    return date_c;
}

void client::setDate_c(const QDate &value)
{
    date_c = value;
}

QString client::getNb_produit() const
{
    return nb_produit;
}

void client::setNb_produit(const QString &value)
{
    nb_produit = value;
}







