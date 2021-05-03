#ifndef ETAGES_H
#define ETAGES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

class Etages
{
public:
    Etages();
    Etages(int,QString);
    //setters
    void setCodeEtage(int CodeEtage){this->CodeEtage=CodeEtage;}
    void setNbPieces(QString NbPieces){this->NbPieces=NbPieces;}
    //getters
    int getCodeEtage(){return CodeEtage;}
    QString getNbPieces(){return NbPieces;}

    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int CodeEtage);


private:
    int CodeEtage;
    QString NbPieces;
};

#endif // ETAGES_H
