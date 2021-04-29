#ifndef LUMIERE_H
#define LUMIERE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>

class Lumiere
{
public:
    Lumiere();
    Lumiere(int,QString,QString,QString);
    //setters
    void setidlum(int idlum){this->idlum=idlum;}
    void setetatlum(QString etatlum){this->etatlum=etatlum;}
    void setduree(QString duree){this->duree=duree;}
    void setpiece(QString piece){this->piece=piece;}

    //getters
    int getidlum(){return idlum;}
    QString getetatlum(){return etatlum;}
    QString getduree(){return duree;}
    QString getpiece(){return piece;}

    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int numero);


private:
    int idlum;
    QString etatlum;
    QString duree;
    QString piece;

};

#endif // DEVOIR_H
