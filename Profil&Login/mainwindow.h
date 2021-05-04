#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QComboBox>
#include "profil.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getCode() const;
    QString get_Nom() const ;
    QString get_Prenom() const ;
    QString get_Location() const;
    QString get_Role() const ;
    QString getid() const;
    QString getUsername() const;
    QString getPassword() const;
    QString getEmail() const;
    QString getPhone() const;

private slots:
    void on_registbtn_clicked();

    void on_pushButton_clicked();

    void on_useraddbtn_clicked();

    void on_suppbtn_clicked();

    void on_logbtn_clicked();
     void fill_form(int);
     void fill_form2(int);

    void on_role_activated(const QString &arg1);

    void on_updateprof_clicked();

    void on_tab_profile_activated(const QModelIndex &index);

    void on_tab_profile_clicked(const QModelIndex &index);
    void on_tab_login_clicked(const QModelIndex &index);


    void on_tab_profile_doubleClicked(const QModelIndex &index);

    void on_suppbtnProf_clicked();

    void on_commandLinkButton_clicked();

    void on_gestionprofil_clicked();

    void on_Nexthome_clicked();

    //void on_search_cursorPositionChanged(int arg1, int arg2);
    void on_searchprof_textChanged(const QString &arg1);
    void recherche(QSqlQueryModel*,QTableView *, QComboBox * , QLineEdit * );
    void on_profiltri_textActivated(const QString &arg1);
    void on_searchlog_cursorPositionChanged(int arg1, int arg2);

    void on_searchlog_textChanged(const QString &arg1);

    void on_returnlog_clicked();

    void on_Createbtn_clicked();

    void on_forgetpw_linkActivated(const QString &link);

    void on_forgetPW_clicked();

    void on_returnPW_clicked();

    void on_GestProfils_3_clicked();

    void on_registerProf_clicked();

    void on_logupdatebtn_clicked();

    void on_tab_login_doubleClicked(const QModelIndex &index);

    void on_suppbtnlog_clicked();

private:
    Ui::MainWindow *ui;
    Login L;

     int selected = 0;
     int selected2= 0;
      QSortFilterProxyModel *proxy;
      profile P;


};
#endif // MAINWINDOW_H
