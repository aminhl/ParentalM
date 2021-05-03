#include "dialog.h"
#include "ui_dialog.h"
#include <QComboBox>
#include <QPrinter>
#include <QPainter>
#include <QPixmap>
#include "exportexcelobject.h"
#include <QMediaPlayer>
#include <QImage>
#include <QDate>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Nabil/Downloads/projet/taraji.png");
    int w = ui->img->width();
    int h = ui->img->height();
    ui->img->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QMediaPlayer * music = new QMediaPlayer();
        music->setMedia(QUrl("C:\\Users\\Nabil\\Downloads\\projet\\chopin.mp3"));
        music->play();
    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(p.afficher());
    ui->tabEtages->setModel(proxy);
    proxy2 = new QSortFilterProxyModel();
    proxy2->setSourceModel(f.afficher());
    ui->tabChambres->setModel(proxy2);

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

void Dialog::on_buttonAjouterEtages_clicked()
{
    int code=ui->spCode->value();
    QString NbPieces=ui->cbNbPieces->currentText();
    Etages p(code,NbPieces);
    QMessageBox msg;
    if(p.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy = new QSortFilterProxyModel();
        proxy->setSourceModel(p.afficher());
        ui->tabEtages->setModel(proxy);
        ui->spCode->clear();
    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();}

void Dialog::on_tabEtages_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from Etages where CODEETAGE= :code");
   query.bindValue(":code",EtagesSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->spCode->setValue(query.value(0).toInt());
           ui->cbNbPieces->setCurrentIndex(2);
           ui->cbNbPieces->setCurrentIndex(ui->cbNbPieces->findText(query.value(1).toString(),Qt::MatchExactly));

       }
   }
}



void Dialog::on_leRecherche_textChanged(const QString &arg1)
{
    recherche(p.afficher(),ui->tabEtages,ui->cbTri,ui->leRecherche);
}

void Dialog::on_buttonSupprimerEtages_clicked()
{
    Etages p;
    QMessageBox msgBox;
    QMessageBox msg;
    if(EtagesSelectionne=="")
    {
         msgBox.setText("Aucun étage n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer l ' etage  "
                       "numéro "+EtagesSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (p.supprimer(EtagesSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy = new QSortFilterProxyModel();
            proxy->setSourceModel(p.afficher());
            ui->tabEtages->setModel(proxy);

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

void Dialog::on_tabEtages_clicked(const QModelIndex &index)
{
    EtagesSelectionne=ui->tabEtages->model()->data(index.sibling(index.row(),0)).toString();
    Etages p;
    p.setCodeEtage(EtagesSelectionne.toInt());


}


void Dialog::on_buttonModifererEtages_clicked()
{
    int code=ui->spCode->value();
    QString NbPieces=ui->cbNbPieces->currentText();
    Etages p(code,NbPieces);

 bool test=p.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy = new QSortFilterProxyModel();
     proxy->setSourceModel(p.afficher());
     ui->tabEtages->setModel(proxy);
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

    ExportExcelObject obj(fileName, "Etages", ui->tabEtages);

    //colums to export
    obj.addField(0, "CODEETAGE", "char(50)");
    obj.addField(1, "NBPIECES", "char(50)");
    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

void Dialog::on_buttonAjouterChambres_clicked()
{
    int refch=ui->sprefch->value();
    QString occ=ui->cbOcc->text();
    QString Nblits=ui->LbNbLits->text();
    QString Superficie=ui->LbSuperficie->text();
    QString Statut=ui->LbStatut->currentText();
    Chambres f(refch,occ,Nblits,Superficie,Statut);
    QMessageBox msg;
    if(f.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy2 = new QSortFilterProxyModel();
        proxy2->setSourceModel(f.afficher());
        ui->tabChambres->setModel(proxy2);
        ui->sprefch->clear();
        ui->LbNbLits->clear();
        ui->LbSuperficie->clear();
        ui->LbStatut->clear();
    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();
}

void Dialog::on_ButtonExcelChambres_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "Chambres", ui->tabChambres);

    //colums to export
    obj.addField(0, "REFCH", "char(50)");
    obj.addField(1, "OCC", "char(50)");
    obj.addField(2, "SUPERFICIE", "char(50)");
    obj.addField(3, "NBLITS", "char(50)");
    obj.addField(4, "STATUT", "char(50)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }

}

void Dialog::on_leRechercheChambres_textChanged(const QString &arg1)
{
    recherche(f.afficher(),ui->tabChambres,ui->cbTriChambres,ui->leRechercheChambres);

}

void Dialog::on_tabChambres_clicked(const QModelIndex &index)
{
    ChambresSelectionne=ui->tabChambres->model()->data(index.sibling(index.row(),0)).toString();
    Chambres f;
    f.setRefCh(ChambresSelectionne.toInt());
}

void Dialog::on_tabChambres_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from Chambres where REFCH= :ref");
   query.bindValue(":ref",ChambresSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->sprefch->setValue(query.value(0).toInt());
           ui->cbOcc->setText(query.value(1).toString());
           ui->LbSuperficie->setText(query.value(2).toString());
           ui->LbNbLits->setText(query.value(3).toString());
           ui->LbStatut->setCurrentIndex(4);
           ui->LbStatut->setCurrentIndex(ui->LbStatut->findText(query.value(1).toString(),Qt::MatchExactly));

       }
   }

}

void Dialog::on_buttonSupprimerChambres_clicked()
{
    Chambres f;
    QMessageBox msgBox;
    QMessageBox msg;
    if(ChambresSelectionne=="")
    {
         msgBox.setText("Aucune chambre n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer la chambre "
                       "numéro "+ChambresSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (f.supprimer(ChambresSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy2 = new QSortFilterProxyModel();
            proxy2->setSourceModel(f.afficher());
            ui->tabChambres->setModel(proxy2);

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

void Dialog::on_buttonModifererChambres_clicked()
{
    int refch=ui->sprefch->value();
    QString occ=ui->cbOcc->text();
    QString Nblits=ui->LbNbLits->text();
    QString Superficie=ui->LbSuperficie->text();
    QString Statut=ui->LbStatut->currentText();
    Chambres f(refch,occ,Nblits,Superficie,Statut);

 bool test=f.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy2 = new QSortFilterProxyModel();
     proxy2->setSourceModel(f.afficher());
     ui->tabChambres->setModel(proxy2);
 }
 else
 {
     msg.setText("echec lors de la  modification");
 }
 msg.exec();

}

void Dialog::on_PDFChambre_clicked()
{
    QPrinter printer;
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setOutputFileName("C://Users//Nabil//Downloads//projet//chambre.pdf");
                    QPainter painter;
                    QImage img("C:\\Users\\Nabil\\Downloads\\projet\\taraji.png");

                    if (! painter.begin(&printer)) { // failed to open file
                        qWarning("failed to open file, is it writable?");
                        QMessageBox::critical(nullptr, QObject::tr("OK"),
                                                                         QObject::tr("failed to open file, is it writable?\n""Click Cancel to exit")
                                                                         ,QMessageBox::Cancel);
                    }

                    QSqlQuery   query ;
                    qDebug() << query.prepare("select sysdate from dual ");
                    if ( query.exec() )
                    {

                      QString S= QDate::currentDate().toString();
                        painter.drawText(850,50,S);
                        QPen penred(Qt::black);
                        painter.drawImage(5,5,img.scaled(130,130));
                        painter.setFont(QFont("Book Antiqua", 30));
                        penred.setWidth(1);
                        painter.setPen(penred);

                        painter.drawText(200,100," Gestion des chambres ");
                        painter.setFont(QFont("Book Antiqua",30));
                        painter.setPen(Qt::black);

                    }

                    QString Ref_Chambre,occupant,superficie,nblits,statut;
                    QSqlQuery   qry ;
                    int i =100;
                    int k=0;
                    qDebug() << qry.prepare("select * from CHAMBRES ");

                    if ( qry.exec() )
                    {

                        while(qry.next())
                        {

                            if ( k % 13 ==0)
                            {   i=250;
                                painter.setFont(QFont("Arial",10));
                                QPen penblack(Qt::black);

                                painter.setPen(penblack);
                painter.drawText (5,200,"Ref_Chambre");
                painter.drawText (180,200,"occupant");
                painter.drawText (300,200,"superficie");
                painter.drawText (400,200,"nblits");
                painter.drawText (550,200,"statut");


                            }

                            painter.setFont(QFont("Arial",10));
                            QPen penblack(Qt::black);

                            painter.setPen(penblack);
                            int j=0;
                            Ref_Chambre= qry.value(0).toString();
                            painter.drawText(j*100,i, Ref_Chambre);
                            j++;
                            occupant=qry.value(1).toString();
                            painter.drawText(j*140,i, occupant);
                            j++;
                           superficie=qry.value(2).toString();
                            painter.drawText(j*140,i, superficie);
                            j++;
                            nblits=qry.value(3).toString();
                            painter.drawText(j*140,i, nblits);
                            j++;
                           statut=qry.value(4).toString();
                            painter.drawText(j*140,i, statut);
                            j++;



                            i+=80;
                            k++;

                        }
                    }

                    painter.end();
}
