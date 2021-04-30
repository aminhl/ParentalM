#ifndef LOISIR_H
#define LOISIR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>


class Loisir
{
public:
    Loisir();
    Loisir(int,QString,QString,QString,QString);
    //setters
    void setNumeroLoisir(int numeroLoisir){this->numeroLoisir=numeroLoisir;}
    void setTypeLoisir(QString typeLoisir){this->typeLoisir=typeLoisir;}
    void setDateLoisir(QString dateLoisir){this->dateLoisir=dateLoisir;}
    void setLieuLoisir(QString lieuLoisir){this->lieuLoisir=lieuLoisir;}
    void setDureeLoisir(QString dureeLoisir){this->dureeLoisir=dureeLoisir;}
    //getters
    int getNumeroLoisir(){return numeroLoisir;}
    QString getTypeLoisir(){return typeLoisir;}
    QString getDateLoisir(){return dateLoisir;}
    QString getLieuLoisir(){return lieuLoisir;}
    QString getDureeLoisir(){return dureeLoisir;}
    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int numero);


private:
    int numeroLoisir;
    QString typeLoisir;
    QString dateLoisir;
    QString lieuLoisir;
    QString dureeLoisir;
};

#endif // LOISIR_H
