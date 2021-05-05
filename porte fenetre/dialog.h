#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QMessageBox>
#include "porte.h"
#include "fenetre.h"
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    void recherche(QSqlQueryModel*,QTableView *, QComboBox * , QLineEdit * );
    ~Dialog();

private slots:
    void on_buttonAjouterPorte_clicked();

    void on_tabPorte_doubleClicked(const QModelIndex &index);

    void on_leRecherche_textChanged(const QString &arg1);

    void on_buttonSupprimerPorte_clicked();

    void on_tabPorte_clicked(const QModelIndex &index);

    void on_buttonModifererPorte_clicked();

    void on_ButtonExcel_clicked();

    void on_buttonAjouterFenetre_clicked();

    void on_ButtonExcelFenetre_clicked();

    void on_leRechercheFenetre_textChanged(const QString &arg1);

    void on_tabFenetre_clicked(const QModelIndex &index);

    void on_tabFenetre_doubleClicked(const QModelIndex &index);

    void on_buttonSupprimerFenetre_clicked();

    void on_buttonModifererFenetre_clicked();

    void on_buttonVideo_clicked();

    void on_buttonPDF_clicked();

    void on_buttonPdfFenetre_clicked();

    void on_buttonVideoFenetre_clicked();

private:
    Ui::Dialog *ui;
    Porte p;
    Fenetre f;
    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy2;
    QString porteSelectionne;
    QString fenetreSelectionne;
    QMediaPlayer* player;
        QVideoWidget* vw;

};

#endif // DIALOG_H
