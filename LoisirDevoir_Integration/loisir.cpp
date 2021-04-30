#include "loisir.h"

Loisir::Loisir()
{

}
Loisir::Loisir(int numeroLoisir,QString typeLoisir,QString lieuLoisir,QString dateLoisir,QString dureeLoisir)
{
    this->numeroLoisir=numeroLoisir;
    this->typeLoisir=typeLoisir;
    this->lieuLoisir=lieuLoisir;
    this->dateLoisir=dateLoisir;
    this->dureeLoisir=dureeLoisir;
}

bool Loisir::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO LOIS (NUMEROLOISIR,TYPELOISIR,LIEULOISIR,DATELOISIR,DUREELOISIR) "
                        "VALUES (:numeroLoisir, :typeLoisir, :lieuLoisir,:dateLoisir,:dureeLoisir)");
    query.bindValue(":numeroLoisir",numeroLoisir );
    query.bindValue(":typeLoisir",typeLoisir); //remplir la valeur d'une maniere securisée
    query.bindValue(":lieuLoisir", lieuLoisir);
    query.bindValue(":dateLoisir", dateLoisir);
    query.bindValue(":dureeLoisir",dureeLoisir);
    return    query.exec();
}

QSqlQueryModel * Loisir::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM LOIS");
    return modal;
}

bool Loisir::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from LOIS where NUMEROLOISIR = :numeroLoisir");
    query.bindValue(":numeroLoisir",numero);
    return query.exec();
}

bool Loisir::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE LOIS SET TYPELOISIR=:typeLoisir,DATELOISIR=:dateLoisir, LIEULOISIR=:lieuLoisir"
                        ", DUREELOISIR=:dureeLoisir WHERE NUMEROLOISIR=:numeroLoisir");
          query.bindValue(":numeroLoisir", numeroLoisir);
          query.bindValue(":typeLoisir", typeLoisir);
          query.bindValue(":dateLoisir", dateLoisir);
          query.bindValue(":lieuLoisir", lieuLoisir);
          query.bindValue(":dureeLoisir", dureeLoisir);
          return query.exec();
}


