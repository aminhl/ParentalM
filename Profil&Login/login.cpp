#include "login.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Login::Login()
{
    id=0;
    username="";
    password="";
    email="";
    phone="";




}

Login::Login(int id , QString username,QString password,QString email,QString phone)
{
this->id=id;
this->username=username ;
this->password= password;
this->email=email ,
this->phone = phone;

}
int Login::getid(){return id;}
QString Login::getUsername(){return username;}
QString Login::getPassword(){return password;}
QString Login::getEmail(){return email;}
QString Login::getPhone(){return phone;}
void Login::setId(int id){this->id=id;}
void Login::setUsername(QString username){this->username=username;}

void Login::setPassword(QString password){this->password=password;}

void Login::setEmail(QString email){this->email=email;}
void Login::setPhone(QString phone){this->phone=phone;}



bool Login::ajouterL(){
    QSqlQuery query;
    QString id_string= QString::number(id);
    QString res= QString::number(id);
    query.prepare("INSERT INTO LOGIN (ID,USERNAME,PASSWORD,EMAIL,PHONE)"
        "VALUES(:id,:username,:password,:email,:phone)");
    query.bindValue(":id",id_string);
     query.bindValue(":username",username);
     query.bindValue(":password",password);
       query.bindValue(":email",email);
        query.bindValue(":phone",phone);
          return  query.exec();

}
QSqlQueryModel* Login::afficher(){
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM login");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("USERNAME"));

model->setHeaderData(2, Qt::Horizontal,QObject::tr("PASSWORD"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("PHONE"));

return model;

}

bool Login::supprimer(int selected2)
{

    QSqlQuery query;
    query.prepare("Delete FROM  LOGIN where id=:sel");
    query.bindValue(":sel",selected2);

    return query.exec();

}
bool Login::modifierL(int selected){

    QSqlQuery query;


    query.prepare(" UPDATE LOGIN SET ID= :id, USERNAME= :username ,PASSWORD= :password ,EMAIL= :email, PHONE= :phone"
                  " where ID= :id");
    query.bindValue(":id", selected);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":email", email);
 query.bindValue(":phone", phone);
    return    query.exec();

}
