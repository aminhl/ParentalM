#include "connexion.h"

Connexion::Connexion()
{}

bool Connexion::ouvrirConnexion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("Source_Projet2A");
    db.setUserName("sofiene");//inserer nom de l'utilisateur
    db.setPassword("esprit18");//inserer mot de passe de cet utilisateur

    if (db.open())
        return true;

    return false;


}
void Connexion::fermerConnexion()
{db.close();}
