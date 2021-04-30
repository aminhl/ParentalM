#ifndef CAMERA_H
#define CAMERA_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>


class Camera
{
public:
    Camera();
    Camera(int,QString,QString);
    //setters
    void setidcam(int idcam){this->idcam=idcam;}
    void setetatcam(QString etatcam){this->etatcam=etatcam;}
    void setemplacement(QString emplacement){this->emplacement=emplacement;}

    //getters
    int Getidcam(){return idcam;}
    QString Getetatcam(){return etatcam;}
    QString Getemplacement(){return emplacement;}

    //crud
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier();
    bool supprimer(int idcam);


private:
    int idcam;
    QString etatcam;
    QString emplacement;

};

#endif // CAMERA_H
