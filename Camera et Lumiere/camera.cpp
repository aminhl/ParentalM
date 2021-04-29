#include "camera.h"

Camera::Camera()
{

}
Camera::Camera(int idcam,QString etatcam,QString emplacement)
{
    this->idcam=idcam;
    this->etatcam=etatcam;
    this->emplacement=emplacement;

}

bool Camera::ajouter()
{
    QSqlQuery query;


    query.prepare("INSERT INTO CAMERA   (IDCAM,ETATCAM,EMPLACEMENT) "
                        "VALUES (:idcam, :etatcam, :emplacement)");
    query.bindValue(":idcam",idcam );
    query.bindValue(":etatcam",etatcam); //remplir la valeur d'une maniere securisée
    query.bindValue(":emplacement", emplacement);

    return    query.exec();
}

QSqlQueryModel * Camera::afficher()
{

    QSqlQueryModel * modal=new QSqlQueryModel();
    modal->setQuery("SELECT *FROM CAMERA");
    return modal;
}

bool Camera::supprimer (int numero)
{

    QSqlQuery query;
    qDebug()<<"numero"<<numero;
    query.prepare("Delete from CAMERA where IDCAM = :idcam");
    query.bindValue(":idcam",numero);
    return query.exec();
}

bool Camera::modifier()
{

    QSqlQuery query;

          query.prepare("UPDATE CAMERA SET ETATCAM=:etatcam,EMPLACEMENT=:emplacement WHERE IDCAM=:idcam");
          query.bindValue(":idcam", idcam);
          query.bindValue(":etatcam", etatcam);
          query.bindValue(":emplacement", emplacement);

          return query.exec();
}


