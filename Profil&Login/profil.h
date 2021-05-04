#ifndef PROFIL_H
#define PROFIL_H
#include <QString>
#include <QSqlQueryModel>



class profile
{
public:
    profile();
    profile(int,QString,QString,QString,QString);
    int getCode();
    QString getNom();
    QString getPrenom();
    QString getLocation();
    QString getRole();
    void setCode(int code);
    void setNom(QString nom);

    void setPrenom(QString prenom);
    void setLocation(QString location);
    void setRole(QString role);
    bool ajouterutil();
    QSqlQueryModel* afficherprof();
    bool modifier(int);
    bool supprimer(int);
private:
    int code;
    QString nom,prenom,location,role;
};

#endif // profile_H
