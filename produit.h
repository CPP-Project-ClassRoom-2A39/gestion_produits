            #ifndef PRODUIT_H
            #define PRODUIT_H
            #include<QString>
            #include <QSqlQuery>
            #include <QSqlQueryModel>
            #include <cstdlib>
            #include <ctime>
            #include <windows.h>
            #include <QDate>

class produit
{
public:
    produit();
    produit(QString id,QString name,QDate date_a,QDate date_e,int quantite,int prix_u,int mod_add);
    void set_id(QString id_p);
    QString get_id();
    void set_name(QString name_p);
    QString get_name();
    int toggle_notif_bar;

    QSqlQueryModel* afficher(QString data,int mode);
    void delete_product(QString data);


    int get_mode_add();
    void set_mode_add(int value);   
    void add_product();
    bool  update_product();
    void set_view_mode(int data);
    int get_view_mode();
    int get_if_emp_added();
    void set_rating(QString data);
    bool update_rating();
    QString get_rating();

    int emp_add;



    QString return_name(QString id_p);
    QString return_quantity(int id_p);
    int state_bar;

    QDate getDate_a();
    void setDate_a(QDate &value);

    QDate getDate_e();
    void setDate_e( QDate &value);

    int getPrix_u();
    void setPrix_u(int value);

    int getQuantite_p();
    void setQuantite_p(int value);
    int get_product_number();
    QVector<QString> list_product_notif();
    QVector<QString> list_mail_fournisseur();
private:
    QString id_p,name_p;
    QDate date_a,date_e;
    int prix_u,quantite_p;
    int mod_add,num_produit;
    int table_mod;
    ////check if the employe is added
    int added_not_added;
    QString rating;

};

#endif
