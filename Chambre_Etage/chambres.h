#ifndef CHAMBRES_H
#define CHAMBRES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>


class Chambres
{
public:
    Chambres();
    Chambres(int,QString,QString,QString,QString);
    //setters
    void setRefCh(int RefCh){this->RefCh=RefCh;}
    void setOcc(QString Occ){this->Occ=Occ;}
    void setSuperficie(QString Superficie){this->Superficie=Superficie;}
    void setNblits(QString Nblits){this->Nblits=Nblits;}
    void setStatut(QString Statut){this->Statut=Statut;}
    //getters
    int getRefCh(){return RefCh;}
    QString getOcc(){return Occ;}
    QString getSuperficie(){return Superficie;}
    QString getNblits(){return Nblits;}
    QString getStatut(){return Statut;}
    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int RefCh);


private:
    int RefCh;
    QString Occ;
    QString Superficie;
    QString Nblits;
    QString Statut;
};

#endif // Chambres_H
