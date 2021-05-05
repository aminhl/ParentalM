#include "porte.h"

Porte::Porte()
{

}
Porte::Porte(int numero,QString etat,QString matiere,QString dimensions,QString description)
{
    this->numero=numero;
    this->etat=etat;
    this->matiere=matiere;
    this->dimensions=dimensions;
    this->description=description;
}

bool Porte::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO PORTE (NUMERO,ETAT,MATIERE,DIMENSIONS,DESCRIPTION) "
                        "VALUES (:num, :etat, :matiere,:dim,:desc)");
    query.bindValue(":num",numero );
    query.bindValue(":etat",etat); //remplir la valeur d'une maniere securisée
    query.bindValue(":matiere", matiere);
    query.bindValue(":dim", dimensions);
    query.bindValue(":desc",description);
    return    query.exec();
}

QSqlQueryModel * Porte::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM PORTE");
    return modal;
}

bool Porte::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from Porte where NUMERO = :num");
    query.bindValue(":num",numero);
    return query.exec();
}

bool Porte::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE PORTE SET ETAT=:etat,DIMENSIONS=:dim, MATIERE=:mat"
                        ", DESCRIPTION=:desc WHERE NUMERO=:num");
          query.bindValue(":num", numero);
          query.bindValue(":etat", etat);
          query.bindValue(":dim", dimensions);
          query.bindValue(":mat", matiere);
          query.bindValue(":desc", description);
          return query.exec();
}


