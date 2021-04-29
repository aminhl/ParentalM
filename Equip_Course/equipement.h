#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>

class equipement
{
public:
    equipement();
    equipement(int,QString,QString,QString,QString);
    //setters
    void setNumero(int numero){this->numero=numero;}
    void setEtat(QString etat){this->etat=etat;}
    void setNom(QString nom){this->nom=nom;}
    void setEmp(QString emp){this->emp=emp;}
    void setType(QString type){this->type=type;}
    //getters
    int getNumero(){return numero;}
    QString getEtat(){return etat;}
    QString getNom(){return nom;}
    QString getEmp(){return emp;}
    QString getType(){return type;}
    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int numero);


private:
    int numero;
    QString etat;
    QString nom;
    QString emp;
    QString type;
};

#endif // EQUIPEMENT_H
