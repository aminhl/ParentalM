#include "profil.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

profile::profile()
{
    code=0;
    nom="";
    prenom="";
    location="";
    role="";
}

profile::profile(int code , QString nom,QString prenom,QString location,QString role)
{
this->code=code;
this->nom=nom ;
this->prenom= prenom;
this->location=location ;
this->role = role;

}
int profile::getCode(){return code;}
QString profile::getNom(){return nom;}
QString profile::getPrenom(){return prenom;}
QString profile::getLocation()    {return location;}
QString profile::getRole(){return role;}
void profile::setCode(int code){this->code=code;}
void profile::setNom(QString nom){this->nom=nom;}

void profile::setPrenom(QString prenom){this->prenom=prenom;}

void profile::setLocation(QString Location){this->location=Location;}
void profile::setRole(QString phone){this->role=phone;}


bool profile::ajouterutil(){
    QSqlQuery query;
    QString code_string= QString::number(code);
  //  QString res= QString::number(code);
    query.prepare("INSERT INTO USE (CODE,NOM,PRENOM,LOCATION,ROLE)"
        "VALUES(:code,:nom,:prenom,:location,:role)");
    query.bindValue(":code",code_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
       query.bindValue(":location",location);
        query.bindValue(":role",role);
          return  query.exec();

}
QSqlQueryModel* profile::afficherprof(){
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM use");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("CODE"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));

model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("LOCATION"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("ROLE"));

return model;

}

bool profile::supprimer(int selected)
{

    QSqlQuery query;
    query.prepare("Delete FROM  USE where code=:sel");
    query.bindValue(":sel",selected);

    return query.exec();

}
bool profile::modifier(int selected){

    QSqlQuery query;


    query.prepare(" UPDATE USE SET CODE= :num_code, NOM= :nom ,PRENOM= :prenom ,LOCATION= :location,ROLE= :role"
                  " where CODE= :num_code");
    query.bindValue(":num_code", selected);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":location", location);
 query.bindValue(":role", role);
    return    query.exec();

}
