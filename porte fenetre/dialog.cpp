#include "dialog.h"
#include "ui_dialog.h"
#include <QComboBox>
#include "exportexcelobject.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(p.afficher());
    ui->tabPorte->setModel(proxy);
    proxy2 = new QSortFilterProxyModel();
    proxy2->setSourceModel(f.afficher());
    ui->tabFenetre->setModel(proxy2);

}

void Dialog::recherche(QSqlQueryModel* model , QTableView * tab, QComboBox * indexColone, QLineEdit * le_recherche)
{
 proxy = new QSortFilterProxyModel();
 proxy->setSourceModel(model);
 proxy->setFilterFixedString(le_recherche->text());
 proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
 proxy->setFilterKeyColumn(indexColone->currentIndex()-1);// chercher dans la coloune ou donner le numero de la colone
 tab->setModel(proxy);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonAjouterPorte_clicked()
{
    int num=ui->spNumero->value();
    QString etat=ui->cbEtat->currentText();
    QString matiere=ui->leMatiere->text();
    QString Dimensions=ui->leDimensions->text();
    QString desc=ui->textDescription->toPlainText();
    Porte p(num,etat,matiere,Dimensions,desc);
    QMessageBox msg;
    if(p.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy = new QSortFilterProxyModel();
        proxy->setSourceModel(p.afficher());
        ui->tabPorte->setModel(proxy);
        ui->spNumero->clear();
        ui->leMatiere->clear();
        ui->leDimensions->clear();
        ui->textDescription->clear();
    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();}

void Dialog::on_tabPorte_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from porte where Numero= :num");
   query.bindValue(":num",porteSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->spNumero->setValue(query.value(0).toInt());
           ui->cbEtat->setCurrentIndex(0);
           ui->cbEtat->setCurrentIndex(ui->cbEtat->findText(query.value(1).toString(),Qt::MatchExactly));
           ui->leDimensions->setText(query.value(2).toString());
           ui->leMatiere->setText(query.value(3).toString());
           ui->textDescription->setPlainText(query.value(4).toString());

       }
   }
}



void Dialog::on_leRecherche_textChanged(const QString &arg1)
{
    recherche(p.afficher(),ui->tabPorte,ui->cbTri,ui->leRecherche);
}

void Dialog::on_buttonSupprimerPorte_clicked()
{
    Porte p;
    QMessageBox msgBox;
    QMessageBox msg;
    if(porteSelectionne=="")
    {
         msgBox.setText("Aucun porte n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer le porte "
                       "numéro "+porteSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (p.supprimer(porteSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy = new QSortFilterProxyModel();
            proxy->setSourceModel(p.afficher());
            ui->tabPorte->setModel(proxy);

            }
            else
            {
                msg.setText("echec de suppression");

            }
             msg.exec();
                break;;

           case QMessageBox::No:
        return;
            break;
     }
}

void Dialog::on_tabPorte_clicked(const QModelIndex &index)
{
    porteSelectionne=ui->tabPorte->model()->data(index.sibling(index.row(),0)).toString();
    Porte p;
    p.setNumero(porteSelectionne.toInt());


}


void Dialog::on_buttonModifererPorte_clicked()
{
    int num=ui->spNumero->value();
    QString etat=ui->cbEtat->currentText();
    QString matiere=ui->leMatiere->text();
    QString Dimensions=ui->leDimensions->text();
    QString desc=ui->textDescription->toPlainText();
    Porte p(num,etat,matiere,Dimensions,desc);

 bool test=p.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy = new QSortFilterProxyModel();
     proxy->setSourceModel(p.afficher());
     ui->tabPorte->setModel(proxy);
 }
 else
 {
     msg.setText("echec lors du modification");
 }
 msg.exec();
}

void Dialog::on_ButtonExcel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "porte", ui->tabPorte);

    //colums to export
    obj.addField(0, "NUMERO", "char(50)");
    obj.addField(1, "ETAT", "char(50)");
    obj.addField(2, "DIMENSIONS", "char(50)");
    obj.addField(3, "MATIERE", "char(50)");
    obj.addField(4, "DESCRIPTION", "char(50)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void Dialog::on_buttonAjouterFenetre_clicked()
{
    int num=ui->spNumeroFenetre->value();
    QString etat=ui->cbEtatFenetre->currentText();
    QString matiere=ui->leMatiereFenetre->text();
    QString Dimensions=ui->leDimensionsFenetre->text();
    QString desc=ui->textDescriptionFenetre->toPlainText();
    Fenetre f(num,etat,matiere,Dimensions,desc);
    QMessageBox msg;
    if(f.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy2 = new QSortFilterProxyModel();
        proxy2->setSourceModel(f.afficher());
        ui->tabFenetre->setModel(proxy2);
        ui->spNumeroFenetre->clear();
        ui->leMatiereFenetre->clear();
        ui->leDimensionsFenetre->clear();
        ui->textDescriptionFenetre->clear();
    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();
}

void Dialog::on_ButtonExcelFenetre_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "fenetre", ui->tabPorte);

    //colums to export
    obj.addField(0, "NUMERO", "char(50)");
    obj.addField(1, "ETAT", "char(50)");
    obj.addField(2, "DIMENSIONS", "char(50)");
    obj.addField(3, "MATIERE", "char(50)");
    obj.addField(4, "DESCRIPTION", "char(50)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }

}

void Dialog::on_leRechercheFenetre_textChanged(const QString &arg1)
{
    recherche(f.afficher(),ui->tabFenetre,ui->cbTriFenetre,ui->leRechercheFenetre);

}

void Dialog::on_tabFenetre_clicked(const QModelIndex &index)
{
    fenetreSelectionne=ui->tabFenetre->model()->data(index.sibling(index.row(),0)).toString();
    Fenetre f;
    f.setNumero(fenetreSelectionne.toInt());
}

void Dialog::on_tabFenetre_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from fenetre where Numero= :num");
   query.bindValue(":num",fenetreSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->spNumeroFenetre->setValue(query.value(0).toInt());
           ui->cbEtatFenetre->setCurrentIndex(0);
           ui->cbEtatFenetre->setCurrentIndex(ui->cbEtatFenetre->findText(query.value(1).toString(),Qt::MatchExactly));
           ui->leDimensionsFenetre->setText(query.value(2).toString());
           ui->leMatiereFenetre->setText(query.value(3).toString());
           ui->textDescriptionFenetre->setPlainText(query.value(4).toString());

       }
   }

}

void Dialog::on_buttonSupprimerFenetre_clicked()
{
    Fenetre f;
    QMessageBox msgBox;
    QMessageBox msg;
    if(fenetreSelectionne=="")
    {
         msgBox.setText("Aucune fenetre n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer la fenetre "
                       "numéro "+fenetreSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (f.supprimer(fenetreSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy2 = new QSortFilterProxyModel();
            proxy2->setSourceModel(f.afficher());
            ui->tabFenetre->setModel(proxy2);

            }
            else
            {
                msg.setText("echec de suppression");

            }
             msg.exec();
                break;;

           case QMessageBox::No:
        return;
            break;
     }
}

void Dialog::on_buttonModifererFenetre_clicked()
{
    int num=ui->spNumeroFenetre->value();
    QString etat=ui->cbEtatFenetre->currentText();
    QString matiere=ui->leMatiereFenetre->text();
    QString Dimensions=ui->leDimensionsFenetre->text();
    QString desc=ui->textDescriptionFenetre->toPlainText();
    Fenetre f(num,etat,matiere,Dimensions,desc);

 bool test=f.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy2 = new QSortFilterProxyModel();
     proxy2->setSourceModel(f.afficher());
     ui->tabFenetre->setModel(proxy2);
 }
 else
 {
     msg.setText("echec lors du modification");
 }
 msg.exec();

}

void Dialog::on_buttonVideo_clicked()
{
      player= new QMediaPlayer;
      vw=new QVideoWidget;

      auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


      player->setVideoOutput(vw);
      player->setMedia(QUrl::fromLocalFile(filename));
      vw->setGeometry(100,100,300,400);
      vw->show();
      player->play();
}

void Dialog::on_buttonPDF_clicked()
{
                         QString strStream;
                             QTextStream out(&strStream);

                             const int rowCount = ui->tabPorte->model()->rowCount();
                             const int columnCount = ui->tabPorte->model()->columnCount();

                             out <<  "<html>\n"
                                 "<head>\n"
                                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 <<  QString("<title>%1</title>\n").arg("strTitle")
                                 <<  "</head>\n"
                                 "<body bgcolor=#ffffff link=#5000A0>\n"

                                //     "<align='right'> " << datefich << "</align>"
                                 "<center> <H1>Portes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                             // headers
                             out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                             for (int column = 0; column < columnCount; column++)
                                 if (!ui->tabPorte->isColumnHidden(column))
                                     out << QString("<th>%1</th>").arg(ui->tabPorte->model()->headerData(column, Qt::Horizontal).toString());
                             out << "</tr></thead>\n";

                             // data table
                             for (int row = 0; row < rowCount; row++) {
                                 out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                 for (int column = 0; column < columnCount; column++) {
                                     if (!ui->tabPorte->isColumnHidden(column)) {
                                         QString data = ui->tabPorte->model()->data(ui->tabPorte->model()->index(row, column)).toString().simplified();
                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                     }
                                 }
                                 out << "</tr>\n";
                             }
                             out <<  "</table> </center>\n"
                                 "</body>\n"
                                 "</html>\n";

                       QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                         if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                        QPrinter printer (QPrinter::PrinterResolution);
                         printer.setOutputFormat(QPrinter::PdfFormat);
                        printer.setPaperSize(QPrinter::A4);
                       printer.setOutputFileName(fileName);

                        QTextDocument doc;
                         doc.setHtml(strStream);
                         doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                         doc.print(&printer);
}

void Dialog::on_buttonPdfFenetre_clicked()
{
    QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tabFenetre->model()->rowCount();
        const int columnCount = ui->tabFenetre->model()->columnCount();

        out <<  "<html>\n"
            "<head>\n"
            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
            "<body bgcolor=#ffffff link=#5000A0>\n"

           //     "<align='right'> " << datefich << "</align>"
            "<center> <H1>fenetre </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tabFenetre->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tabFenetre->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->tabFenetre->isColumnHidden(column)) {
                    QString data = ui->tabFenetre->model()->data(ui->tabFenetre->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table> </center>\n"
            "</body>\n"
            "</html>\n";

  QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

   QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
   printer.setPaperSize(QPrinter::A4);
  printer.setOutputFileName(fileName);

   QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void Dialog::on_buttonVideoFenetre_clicked()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");

    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}
