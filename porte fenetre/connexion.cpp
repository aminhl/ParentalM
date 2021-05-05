#include "connexion.h"

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("projet");
    db.setUserName("bechir");//inserer nom de l'utilisateur
    db.setPassword("bechir");//inserer mot de passe de cet utilisateur

    if (db.open())
        return true;

    return false;


}
void Connexion::fermerConnexion()
{db.close();}
