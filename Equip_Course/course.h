#ifndef COURSE_H
#define COURSE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>


class course
{
public:
    course();
    course(int,QString,QString,QString,QString);
    //setters
    void setNumero(int numero){this->numero=numero;}
    void setTime(QString time){this->time=time;}
    void setTache(QString tache){this->tache=tache;}
    void setStatus(QString status){this->status=status;}
    void setDate(QString date){this->date=date;}
    //getters
    int getNumero(){return numero;}
    QString getTime(){return time;}
    QString getTache(){return tache;}
    QString getStatus(){return status;}
    QString getDate(){return date;}
    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int numero);


private:
    int numero;
    QString time;
    QString tache;
    QString status;
    QString date;
};

#endif // COURSE_H
