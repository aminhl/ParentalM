#ifndef LOISIRDEVOIR_H
#define LOISIRDEVOIR_H

#include <QDialog>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QMessageBox>
#include "lumiere.h"
#include "camera.h"
#include <QDialog>
#include <QFileDialog>
#include <QTimer>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QTextTableFormat>
#include <QStandardItemModel>

namespace Ui {
class LoisirDevoir;
}

class LoisirDevoir : public QDialog
{
    Q_OBJECT

public:
    explicit LoisirDevoir(QWidget *parent = nullptr);

    void recherche(QSqlQueryModel*,QTableView *, QComboBox * , QLineEdit * );
    ~LoisirDevoir();

private slots:
    void on_leRecherche_textChanged(const QString &arg1);

    void on_buttonAjouterDevoir_clicked();

    void on_buttonModifererDevoir_clicked();

    void on_buttonSupprimerDevoir_clicked();

    void on_tabDevoir_doubleClicked(const QModelIndex &index);

    void on_tabDevoir_clicked(const QModelIndex &index);

    void on_buttonAjouterLoisir_clicked();

    void on_buttonModifererLoisir_clicked();

    void on_buttonSupprimerLoisir_clicked();

    void on_tabLoisir_clicked(const QModelIndex &index);

    void on_leRechercheLoisir_textChanged(const QString &arg1);

    void on_tabLoisir_doubleClicked(const QModelIndex &index);

    void on_DevoirVideo_clicked();

    void on_ImprimerLoisir_clicked();

    void myfunction_amine();

    void on_TradEngDev_clicked();

    void on_TradFrDev_clicked();

    void on_TradGerDev_clicked();

    void on_TradEngLois_clicked();

    void on_TradFrLois_clicked();

    void on_TradGerLois_clicked();

    void on_PdfLoisir_clicked();

    void on_DvExl_clicked();

    void on_LoisXl_clicked();

    void on_tablumiere_clicked(const QModelIndex &index);

    void on_tablumiere_doubleClicked(const QModelIndex &index);

    void on_buttonAjoutercamera_clicked();

    void on_buttonModiferercamera_clicked();

    void on_buttonSupprimercamera_clicked();

    void on_tabcamera_doubleClicked(const QModelIndex &index);

    void on_tabcamera_clicked(const QModelIndex &index);

private:
    Ui::LoisirDevoir *ui;
    Lumiere d;
    Camera l;
    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy2;
    QString devoirSelectionne;
    QString loisirSelectionne;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QTimer *timer;

};

#endif // LOISIRDEVOIR_H
