#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQueryModel>



class Login
{
public:
    Login();
    Login(int,QString,QString,QString,QString);
    int getid();
    QString getUsername();
    QString getPassword();
    QString getEmail();
    QString getPhone();
    void setId(int id);
    void setUsername(QString username);

    void setPassword(QString password);
    void setEmail(QString email);
    void setPhone(QString phone);
    bool ajouterL();
    bool modifierL(int);
    QSqlQueryModel* afficher();
    bool supprimer(int);
private:
    int id;
    QString username,password,email,phone;
};

#endif // LOGIN_H
