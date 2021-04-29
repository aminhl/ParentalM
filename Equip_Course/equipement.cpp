#include "equipement.h"

equipement::equipement()
{

}
equipement::equipement(int numero,QString etat,QString emp,QString nom,QString type)
{
    this->numero=numero;
    this->etat=etat;
    this->emp=emp;
    this->nom=nom;
    this->type=type;
}

bool equipement::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO TAB_EQUIPEMENT (NUMERO,ETAT,EMPLACEMENT,NOM,TYPE) "
                        "VALUES (:num, :etat, :emp,:nm,:desc)");
    query.bindValue(":num",numero );
    query.bindValue(":etat",etat); //remplir la valeur d'une maniere securisée
    query.bindValue(":emp", emp);
    query.bindValue(":nm", nom);
    query.bindValue(":desc",type);
    return    query.exec();
}

QSqlQueryModel * equipement::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM TAB_EQUIPEMENT");
    return modal;
}

bool equipement::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from TAB_EQUIPEMENT where NUMERO = :num");
    query.bindValue(":num",numero);
    return query.exec();
}

bool equipement::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE TAB_EQUIPEMENT SET ETAT=:etat,NOM=:nm, EMPLACEMENT=:mat"
                        ", TYPE=:desc WHERE NUMERO=:num");
          query.bindValue(":num", numero);
          query.bindValue(":etat", etat);
          query.bindValue(":nm", nom);
          query.bindValue(":mat", emp);
          query.bindValue(":desc", type);
          return query.exec();
}


