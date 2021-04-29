#include "connexion.h"

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("projet_lou");
    db.setUserName("louay");//inserer nom de l'utilisateur
    db.setPassword("louay");//inserer mot de passe de cet utilisateur

    if (db.open())
        return true;

    return false;


}
void Connexion::fermerConnexion()
{db.close();}
