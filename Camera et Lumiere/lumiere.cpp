#include "lumiere.h"

Lumiere::Lumiere()
{

}
Lumiere::Lumiere(int idlum,QString etatlum,QString duree,QString piece)
{
    this->idlum=idlum;
    this->etatlum=etatlum;
    this->duree=duree;
    this->piece=piece;

}

bool Lumiere::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO LUMIERE (IDLUM,ETATLUM,DUREE,PIECE) "
                        "VALUES (:idlum, :etatlum, :duree,:piece)");
    query.bindValue(":idlum",idlum );
    query.bindValue(":etatlum",etatlum); //remplir la valeur d'une maniere securisée
    query.bindValue(":duree", duree);
    query.bindValue(":piece", piece);

    return    query.exec();
}

QSqlQueryModel * Lumiere::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM LUMIERE");
    return modal;
}

bool Lumiere::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from LUMIERE where IDLUM = :idlum");
    query.bindValue(":idlum",numero);
    return query.exec();
}

bool Lumiere::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE LUMIERE SET ETATLUM=:etatlum,DUREE=:duree, PIECE=:piece"
                        " WHERE IDLUM=:idlum");
          query.bindValue(":idlum", idlum);
          query.bindValue(":etatlum", etatlum);
          query.bindValue(":duree", duree);
          query.bindValue(":piece", piece);

          return query.exec();
}


