#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection
{ QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeConnexion();
};

#endif // CONNECTION_H

