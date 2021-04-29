#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QMessageBox>
#include "equipement.h"
#include "course.h"
#include <QDialog>
#include <QFileDialog>
#include <QPrinter>
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
    void on_buttonAjouterEquip_clicked();

    void on_tabEquip_doubleClicked(const QModelIndex &index);

    void on_leRecherche_textChanged(const QString &arg1);

    void on_buttonSupprimerEquip_clicked();

    void on_tabEquip_clicked(const QModelIndex &index);

    void on_buttonModifererEquip_clicked();

    void on_ButtonExcel_clicked();

    void on_buttonAjouterCourse_clicked();

    void on_ButtonExcelCourse_clicked();

    void on_leRechercheCourse_textChanged(const QString &arg1);

    void on_tabCourse_clicked(const QModelIndex &index);

    void on_tabCourse_doubleClicked(const QModelIndex &index);

    void on_buttonSupprimerCourse_clicked();

    void on_buttonModifererCourse_clicked();
   void  on_excel_clicked();

   void on_leRecherche_cursorPositionChanged(int arg1, int arg2);

   void on_cbTri_textActivated(const QString &arg1);
   void on_PdfCourse_clicked();
void on_PdfEquip_clicked();
void on_checkBox_traduction_arabe_clicked();
private:
    Ui::Dialog *ui;
    equipement p;
    course f;
    QSortFilterProxyModel *proxy;
    QSortFilterProxyModel *proxy2;
    QString EquipSelectionne;
    QString courseSelectionne;

};

#endif // DIALOG_H
