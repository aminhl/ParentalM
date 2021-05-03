#include "Etages.h"

Etages::Etages()
{

}
Etages::Etages(int CodeEtage,QString NbPieces)
{
    this->CodeEtage=CodeEtage;
    this->NbPieces=NbPieces;

}

bool Etages::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO ETAGES (CODEETAGE,NBPIECES) "
                        "VALUES (:code, :nbpieces)");
    query.bindValue(":code",CodeEtage );
    query.bindValue(":nbpieces",NbPieces); //remplir la valeur d'une maniere securisée
    return    query.exec();
}

QSqlQueryModel * Etages::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM Etages");
    return modal;
}

bool Etages::supprimer (int CodeEtage)
{

    QSqlQuery query;
    qDebug()<<"CodeEtage"<<CodeEtage;
    query.prepare("Delete from ETAGES where CODEETAGE = :code");
    query.bindValue(":code",CodeEtage);
    return query.exec();
}

bool Etages::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE ETAGES SET NBPIECES=:nbpieces WHERE CODEETAGE=:code");
          query.bindValue(":code", CodeEtage);
          query.bindValue(":nbpieces", NbPieces);
          return query.exec();
}


