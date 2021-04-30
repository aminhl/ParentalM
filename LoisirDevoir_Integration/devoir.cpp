#include "devoir.h"

Devoir::Devoir()
{

}
Devoir::Devoir(int numeroDevoir,QString diffDevoir,QString statutDevoir,QString tacheDevoir,QString dateDevoir)
{
    this->numeroDevoir=numeroDevoir;
    this->diffDevoir=diffDevoir;
    this->statutDevoir=statutDevoir;
    this->tacheDevoir=tacheDevoir;
    this->dateDevoir=dateDevoir;
}

bool Devoir::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO DEV (NUMERODEVOIR,DIFFDEVOIR,STATUTDEVOIR,TACHEDEVOIR,DATEDEVOIR) "
                        "VALUES (:numeroDevoir, :diffDevoir, :statutDevoir,:tacheDevoir,:dateDevoir)");
    query.bindValue(":numeroDevoir",numeroDevoir );
    query.bindValue(":diffDevoir",diffDevoir); //remplir la valeur d'une maniere securisée
    query.bindValue(":statutDevoir", statutDevoir);
    query.bindValue(":tacheDevoir", tacheDevoir);
    query.bindValue(":dateDevoir",dateDevoir);
    return    query.exec();
}

QSqlQueryModel * Devoir::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM DEV");
    return modal;
}

bool Devoir::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from DEV where NUMERODEVOIR = :numeroDevoir");
    query.bindValue(":numeroDevoir",numero);
    return query.exec();
}

bool Devoir::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE DEV SET DIFFDEVOIR=:diffDevoir,TACHEDEVOIR=:tacheDevoir, STATUTDEVOIR=:statutDevoir"
                        ", DATEDEVOIR=:dateDevoir WHERE NUMERODEVOIR=:numeroDevoir");
          query.bindValue(":numeroDevoir", numeroDevoir);
          query.bindValue(":diffDevoir", diffDevoir);
          query.bindValue(":tacheDevoir", tacheDevoir);
          query.bindValue(":statutDevoir", statutDevoir);
          query.bindValue(":dateDevoir", dateDevoir);
          return query.exec();
}


