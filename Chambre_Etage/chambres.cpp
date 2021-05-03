#include "Chambres.h"

Chambres::Chambres()
{

}
Chambres::Chambres(int RefCh,QString Occ,QString Nblits,QString Superficie,QString Statut)
{
    this->RefCh=RefCh;
    this->Occ=Occ;
    this->Nblits=Nblits;
    this->Superficie=Superficie;
    this->Statut=Statut;
}

bool Chambres::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO Chambres (REFCH,OCC,SUPERFICIE,NBLITS,STATUT) "
                        "VALUES (:ref, :occ, :sup,:nblits,:statut)");
    query.bindValue(":ref",RefCh );
    query.bindValue(":occ",Occ); //remplir la valeur d'une maniere securisée
    query.bindValue(":sup", Superficie);
    query.bindValue(":nblits", Nblits);
    query.bindValue(":statut",Statut);
    return    query.exec();
}

QSqlQueryModel * Chambres::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM Chambres");
    return modal;
}

bool Chambres::supprimer (int RefCh)
{

    QSqlQuery query;
    qDebug()<<"RefCh"<<RefCh;
    query.prepare("Delete from Chambres where REFCH = :ref");
    query.bindValue(":ref",RefCh);
    return query.exec();
}

bool Chambres::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE Chambres SET OCC=:occ,SUPERFICIE=:sup, NBLITS=:nblits"
                        ", STATUT=:statut WHERE REFCH=:ref");
          query.bindValue(":ref", RefCh);
          query.bindValue(":occ", Occ);
          query.bindValue(":sup", Superficie);
          query.bindValue(":nblits", Nblits);
          query.bindValue(":statut", Statut);
          return query.exec();
}


