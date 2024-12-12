#include "produit.h"
#include<QDebug>
produit::produit()
{
    id_p="";
    name_p="";
    prix_u=0;
    quantite_p=0;
    mod_add=0;
    table_mod=0;
    num_produit=0;
     state_bar=0;

}
produit::produit(QString id,QString name,QDate date_a,QDate date_e,int quantite,int prix_u,int mod_add)
{
    this->id_p=id;
    this->name_p=name;
    this->date_a=date_a;
    this->date_e=date_e;
    this->prix_u=prix_u;
    this->quantite_p=quantite;
    this->mod_add=mod_add;

}
void produit:: set_id(QString id){this->id_p=id;}
QString produit:: get_id(){return id_p;}
void produit:: set_name(QString name){this->name_p=name;}
QString produit:: get_name(){return name_p;}

QDate produit:: getDate_a() {return date_a;};
void produit:: setDate_a(QDate &value){this->date_a=value;};

QDate produit::getDate_e(){return date_e; };
void produit::setDate_e(QDate &value){this->date_e=value;};

int produit::getPrix_u(){return prix_u;} ;
void produit::setPrix_u(int value){this->prix_u=value;};

int produit::getQuantite_p(){return quantite_p;} ;
void produit::setQuantite_p(int value){this->quantite_p=value;}

int produit::get_product_number()
{


        QSqlQuery query;
            query.prepare("SELECT COUNT(*) AS product_count FROM produit WHERE quantite < 10");

            if (!query.exec()) {
                return 0;
            }

            if (query.next()) {
                num_produit = query.value("product_count").toInt();
                return num_produit;
            } else {
                qDebug() << "No data found.";
                return 0;
            }
            return num_produit;
}

QVector<QString> produit::list_product_notif()
{

        QVector<QString> productNames;
        QSqlQuery query;
        query.prepare("SELECT nom_p FROM produit WHERE quantite < 10");
        if (!query.exec()) {
            return productNames;
        }
        while (query.next()) {
            QString name = query.value("nom_p").toString();
            productNames.append(name);
        }

        return productNames;

}

QVector<QString> produit::list_mail_fournisseur()
{
    QVector<QString> mailList;
    QSqlQuery query;
        query.prepare("SELECT mail_f FROM fournisseur");
        if (query.exec()) {
            while (query.next()) {
                QString mail = query.value("mail_f").toString();
                mailList.append(mail);
            }
        } else {

        }
        return mailList;
}


int produit::get_mode_add(){return mod_add;}
void produit::set_mode_add(int value){this->mod_add=value;}
QSqlQueryModel* produit::afficher(QString data,int mode)
{

    QSqlQueryModel* model=new QSqlQueryModel();
      if(mode==0)
       model->setQuery("select * from produit");
       if(mode==1)
       {
           model->setQuery("select * from produit where id_p like '" + data + "%'");
       }

       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("id_product"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("name_product"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("Price"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("Quantity"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("Date_A"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("Date_E"));



    return model;
}
void produit::add_product()
{
    QString query;
    QSqlQuery qry;
    qry.prepare("INSERT INTO produit (id_p, nom_p, prix, quantite, date_a, date_e)""VALUES (:user_name,:name,:prix,:quantite,:date_a,:date_e)");

    qry.bindValue(":user_name",get_id());
    qry.bindValue(":name",get_name());
    qry.bindValue(":prix",getPrix_u());
    qry.bindValue(":quantite",getQuantite_p());
    qry.bindValue(":date_a",getDate_a());
    qry.bindValue(":date_e",getDate_e());
    if(qry.exec())
       added_not_added=1;
    else
      added_not_added=0;
qInfo()<<added_not_added;
}
void produit::delete_product(QString data)
{
    QString query;
    QSqlQuery qry;
    qInfo()<<data;
    qry.prepare("DELETE FROM produit where id_p=:id_p");
    qry.bindValue(":id_p",data.toInt());
    qry.exec();
}

bool produit::update_product() {
    QSqlQuery qry;
    qry.prepare("UPDATE produit SET id_p = :id_p, "
                "nom_p = :nom_p, "
                "prix = :prix, "
                "quantite = :quantite, "
                "date_a = :date_a, "
                "date_e = :date_e "
                "WHERE id_p = :user_name");

    qry.bindValue(":id_p", id_p);
    qry.bindValue(":nom_p", get_name());
    qry.bindValue(":prix", getPrix_u());
    qry.bindValue(":quantite", getQuantite_p());
    qry.bindValue(":date_a", date_a);
    qry.bindValue(":date_e", date_e);
    qry.bindValue(":user_name", id_p);

    return qry.exec();
}


void produit::set_view_mode(int data)
{
    this->table_mod=data;
}
int produit::get_view_mode()
{
    return  table_mod;
}
int produit::get_if_emp_added()
{
    return added_not_added;
}






