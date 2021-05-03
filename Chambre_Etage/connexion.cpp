#include "connexion.h"

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("test-bd");
    db.setUserName("nabil");//inserer nom de l'utilisateur
    db.setPassword("nabil");//inserer mot de passe de cet utilisateur

    if (db.open())
        return true;

    return false;


}
void Connexion::fermerConnexion()
{db.close();}
