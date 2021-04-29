#ifndef DEVOIR_H
#define DEVOIR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMediaPlayer>
#include <QVideoWidget>

class Devoir
{
public:
    Devoir();
    Devoir(int,QString,QString,QString,QString);
    //setters
    void setNumeroDevoir(int numeroDevoir){this->numeroDevoir=numeroDevoir;}
    void setDiffDevoir(QString diffDevoir){this->diffDevoir=diffDevoir;}
    void setTacheDevoir(QString tacheDevoir){this->tacheDevoir=tacheDevoir;}
    void setStatutDevoir(QString statutDevoir){this->statutDevoir=statutDevoir;}
    void setDateDevoir(QString dateDevoir){this->dateDevoir=dateDevoir;}
    //getters
    int getNumeroDevoir(){return numeroDevoir;}
    QString getDiffDevoir(){return diffDevoir;}
    QString getTacheDevoir(){return tacheDevoir;}
    QString getStatutDevoir(){return statutDevoir;}
    QString getDateDevoir(){return dateDevoir;}
    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int numero);


private:
    int numeroDevoir;
    QString diffDevoir;
    QString tacheDevoir;
    QString statutDevoir;
    QString dateDevoir;
};

#endif // DEVOIR_H
