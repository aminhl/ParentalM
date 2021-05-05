
#ifndef FENETRE_H
#define FENETRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>


class Fenetre
{
public:
    Fenetre();
    Fenetre(int,QString,QString,QString,QString);
    //setters
    void setNumero(int numero){this->numero=numero;}
    void setEtat(QString etat){this->etat=etat;}
    void setDimensions(QString dimensions){this->dimensions=dimensions;}
    void setMatiere(QString matiere){this->matiere=matiere;}
    void setDescription(QString description){this->description=description;}
    //getters
    int getNumero(){return numero;}
    QString getEtat(){return etat;}
    QString getDimensions(){return dimensions;}
    QString getMatiere(){return matiere;}
    QString getDescription(){return description;}
    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int numero);


private:
    int numero;
    QString etat;
    QString dimensions;
    QString matiere;
    QString description;
};

#endif // FENETRE_H
