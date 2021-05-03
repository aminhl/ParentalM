#include "course.h"

course::course()
{

}
course::course(int numero,QString time,QString status,QString tache,QString date)
{
    this->numero=numero;
    this->time=time;
    this->status=status;
    this->tache=tache;
    this->date=date;
}

bool course::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO TAB_COURSE (NUMERO,TIME,STATUS,TACHE,DATE_C) "
                        "VALUES (:num, :time, :status,:dim,:desc)");
    query.bindValue(":num",numero );
    query.bindValue(":time",time); //remplir la valeur d'une maniere securisée
    query.bindValue(":status", status);
    query.bindValue(":dim", tache);
    query.bindValue(":desc",date);
    return    query.exec();
}

QSqlQueryModel * course::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM TAB_COURSE");
    return modal;
}

bool course::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from TAB_COURSE where NUMERO = :num");
    query.bindValue(":num",numero);
    return query.exec();
}

bool course::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE TAB_COURSE SET TIME=:time,TACHE=:dim, STATUS=:mat"
                        ", DATE_C=:desc WHERE NUMERO=:num");
          query.bindValue(":num", numero);
          query.bindValue(":time", time);
          query.bindValue(":dim", tache);
          query.bindValue(":mat", status);
          query.bindValue(":desc", date);
          return query.exec();
}


