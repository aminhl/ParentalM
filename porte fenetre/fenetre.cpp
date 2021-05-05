#include "fenetre.h"

Fenetre::Fenetre()
{

}
Fenetre::Fenetre(int numero,QString etat,QString matiere,QString dimensions,QString description)
{
    this->numero=numero;
    this->etat=etat;
    this->matiere=matiere;
    this->dimensions=dimensions;
    this->description=description;
}

bool Fenetre::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO Fenetre (NUMERO,ETAT,MATIERE,DIMENSIONS,DESCRIPTION) "
                        "VALUES (:num, :etat, :matiere,:dim,:desc)");
    query.bindValue(":num",numero );
    query.bindValue(":etat",etat); //remplir la valeur d'une maniere securisée
    query.bindValue(":matiere", matiere);
    query.bindValue(":dim", dimensions);
    query.bindValue(":desc",description);
    return    query.exec();
}

QSqlQueryModel * Fenetre::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM Fenetre");
    return modal;
}

bool Fenetre::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from Fenetre where NUMERO = :num");
    query.bindValue(":num",numero);
    return query.exec();
}

bool Fenetre::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE Fenetre SET ETAT=:etat,DIMENSIONS=:dim, MATIERE=:mat"
                        ", DESCRIPTION=:desc WHERE NUMERO=:num");
          query.bindValue(":num", numero);
          query.bindValue(":etat", etat);
          query.bindValue(":dim", dimensions);
          query.bindValue(":mat", matiere);
          query.bindValue(":desc", description);
          return query.exec();
}


