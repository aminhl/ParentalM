#include "LoisirDevoir.h"
#include "ui_LoisirDevoir.h"
#include <QComboBox>
#include <QMessageBox>
#include <QPrinter>
#include <QDate>
#include <QDateTime>
#include <QPainter>
#include <QDebug>
#include <QImage>
#include<QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include<QFileDialog>

LoisirDevoir::LoisirDevoir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoisirDevoir)
{
    ui->setupUi(this);

    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(d.afficher());
    ui->tablumiere->setModel(proxy);
    proxy2 = new QSortFilterProxyModel();
    proxy2->setSourceModel(l.afficher());
    ui->tabcamera->setModel(proxy2);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction_amine()));
    timer->start(1000);

}

void LoisirDevoir::recherche(QSqlQueryModel* model , QTableView * tab, QComboBox * indexColone, QLineEdit * le_rechercheDevoir)
{
 proxy = new QSortFilterProxyModel();
 proxy->setSourceModel(model);
 proxy->setFilterFixedString(le_rechercheDevoir->text());
 proxy->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
 proxy->setFilterKeyColumn(indexColone->currentIndex()-1);// chercher dans la coloune ou donner le numero de la colone
 tab->setModel(proxy);
}

LoisirDevoir::~LoisirDevoir()
{
    delete ui;
}



void LoisirDevoir::on_buttonAjouterDevoir_clicked()
{
    int idlum=ui->idlum->value();
    QString etatlum=ui->etatlum->currentText();
    QString duree=ui->duree->text();
    QString piece=ui->piece->text();
    Lumiere d(idlum,etatlum,duree,piece);
    QMessageBox msg;
    if(d.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy = new QSortFilterProxyModel();
        proxy->setSourceModel(d.afficher());
        ui->tablumiere->setModel(proxy);
        ui->idlum->clear();
        ui->duree->clear();
        ui->piece->clear();

    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();
}

void LoisirDevoir::on_tablumiere_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from LUMIERE where IDLUM= :idlum");
   query.bindValue(":idlum",devoirSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->idlum->setValue(query.value(0).toInt());
           ui->etatlum->setCurrentIndex(0);
           ui->etatlum->setCurrentIndex(ui->etatlum->findText(query.value(1).toString(),Qt::MatchExactly));
           ui->duree->setText(query.value(2).toString());
           ui->piece->setText(query.value(3).toString());


       }
   }
}


void LoisirDevoir::on_leRecherche_textChanged(const QString &arg1)
{
    recherche(d.afficher(),ui->tablumiere,ui->cbTricamera,ui->leRecherchecamera);
}

void LoisirDevoir::on_buttonSupprimerDevoir_clicked()
{
    Lumiere d;
    QMessageBox msgBox;
    QMessageBox msg;
    if(devoirSelectionne=="")
    {
         msgBox.setText("Aucun Devoir n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer le Devoir "
                       "numéro "+devoirSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (d.supprimer(devoirSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy = new QSortFilterProxyModel();
            proxy->setSourceModel(d.afficher());
            ui->tablumiere->setModel(proxy);

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

void LoisirDevoir::on_tablumiere_clicked(const QModelIndex &index)
{
    devoirSelectionne=ui->tablumiere->model()->data(index.sibling(index.row(),0)).toString();
    Lumiere d;
    d.setidlum(devoirSelectionne.toInt());


}



void LoisirDevoir::on_buttonModifererDevoir_clicked()
{
    int num=ui->idlum->value();
    QString etat=ui->etatlum->currentText();
    QString matiere=ui->duree->text();
    QString Dimensions=ui->piece->text();

    Lumiere d(num,etat,matiere,Dimensions);

 bool test=d.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy = new QSortFilterProxyModel();
     proxy->setSourceModel(d.afficher());
     ui->tablumiere->setModel(proxy);
 }
 else
 {
     msg.setText("echec lors du modification");
 }
 msg.exec();
}

/*void LoisirDevoir::on_buttonAjouterLoisir_clicked()
{
    int num=ui->NumeroLois->value();
    QString etat=ui->TypeLois->currentText();

    QString Dimensions=ui->DateLois->text();

    Camera l(num,etat,Dimensions);
    QMessageBox msg;
    if(l.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy2 = new QSortFilterProxyModel();
        proxy2->setSourceModel(l.afficher());
        ui->tabcamera->setModel(proxy2);
        ui->NumeroLois->clear();

        ui->DateLois->clear();

    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();
}*/

void LoisirDevoir::on_leRechercheLoisir_textChanged(const QString &arg1)
{
    recherche(l.afficher(),ui->tabcamera,ui->cbTricamera,ui->leRecherchecamera);

}

/*void LoisirDevoir::on_tabLoisir_clicked(const QModelIndex &index)
{
    loisirSelectionne=ui->tabcamera->model()->data(index.sibling(index.row(),0)).toString();
    Camera l;
    l.setidcam(loisirSelectionne.toInt());
}*/

/*void LoisirDevoir::on_tabLoisir_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from CAMERA where IDCAM= :idcam");
   query.bindValue(":idcam",loisirSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->NumeroLois->setValue(query.value(0).toInt());
           ui->TypeLois->setCurrentIndex(0);
           ui->TypeLois->setCurrentIndex(ui->TypeLois->findText(query.value(1).toString(),Qt::MatchExactly));
           ui->DateLois->setText(query.value(2).toString());


       }
   }

}*/

/*void LoisirDevoir::on_buttonSupprimerLoisir_clicked()
{
    Camera l;
    QMessageBox msgBox;
    QMessageBox msg;
    if(loisirSelectionne=="")
    {
         msgBox.setText("Aucune Loisir n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer le Loisir "
                       "numéro "+loisirSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (l.supprimer(loisirSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy2 = new QSortFilterProxyModel();
            proxy2->setSourceModel(l.afficher());
            ui->tabcamera->setModel(proxy2);

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
}*/

/*void LoisirDevoir::on_buttonModifererLoisir_clicked()
{
    int num=ui->NumeroLois->value();
    QString etat=ui->TypeLois->currentText();

    QString Dimensions=ui->DateLois->text();

    Camera l(num,etat,Dimensions);

 bool test=l.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy2 = new QSortFilterProxyModel();
     proxy2->setSourceModel(l.afficher());
     ui->tabcamera->setModel(proxy2);
 }
 else
 {
     msg.setText("echec lors du modification");
 }
 msg.exec();

}
*/

void LoisirDevoir::on_DevoirVideo_clicked()
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

void LoisirDevoir::on_ImprimerLoisir_clicked()
{
    const QString format("<td>%1</td>");
               QString html;
               QAbstractItemModel *md = ui->tabcamera->model();
               html = "<html><body><table border=\"0\">";

               html += "<td></td>";
               for(int column = 0; column < md->columnCount();
                   column++) {
                   QString data = md->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
                   html += format.arg(data);
               }
               for(int row = 0; row < md->rowCount() ; row++) {
                   html += "<tr>";
                   QString data = md->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
                   html += format.arg(data);
                   for(int column = 0; column < md->columnCount();
                       column++) {
                       QString data = md->index(row, column).data(Qt::DisplayRole).toString();
                       html += format.arg(data);
                   }
                   html += "</tr>";
               }
               html += "</table></body></html>";

               QPrinter printer;
               QPrintDialog *dialog = new QPrintDialog(&printer);
               if(dialog->exec() == QDialog::Accepted) {
                   QTextDocument document;
                   document.setHtml(html);
                   document.print(&printer);
               }
}

void LoisirDevoir::myfunction_amine(){
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss ");
    ui->label_date_time->setText(time_text);
}





void LoisirDevoir::on_TradEngLois_clicked()
{
    ui->tabWidget->setTabText(0,"Duty");
     ui->tabWidget->setTabText(1,"Leisure");

     ui->NumLoisir->setText( tr("Leisure Code"));
            ui->TypeLoisir->setText( tr("Leisure Type"));
            ui->DateLoisir->setText( tr("Leisure Date"));


            ui->buttonAjoutercamera->setText( tr("Add"));
            ui->buttonModiferercamera->setText( tr("Modify"));
            ui->buttonSupprimercamera->setText( tr("Delete"));
}

void LoisirDevoir::on_TradFrLois_clicked()
{
    ui->tabWidget->setTabText(0,"Devoir");
     ui->tabWidget->setTabText(1,"Loisir");

     ui->NumLoisir->setText( tr("Numéro Loisir"));
            ui->TypeLoisir->setText( tr("Type Loisir"));
            ui->DateLoisir->setText( tr("Date Loisir"));
            ui->buttonAjoutercamera->setText( tr("Ajouter"));
            ui->buttonModiferercamera->setText( tr("Modifier"));
            ui->buttonSupprimercamera->setText( tr("Supprimer"));
}

void LoisirDevoir::on_TradGerLois_clicked()
{
   ui->tabWidget->setTabText(0,"Pflicht");
   ui->tabWidget->setTabText(1,"Freizeit");

   ui->NumLoisir->setText( tr("Freizeitnummer"));
   ui->TypeLoisir->setText( tr("Typ Freizeit"));
   ui->DateLoisir->setText( tr("Datiert"));

    ui->buttonAjoutercamera->setText( tr("Hinzufügen"));
    ui->buttonModiferercamera->setText( tr("Bearbeiten"));
    ui->buttonSupprimercamera->setText( tr("Entfernen"));
}

void LoisirDevoir::on_PdfLoisir_clicked()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C://Users//user//Desktop//projet//loisir.pdf");
    QPainter painter;


    if (! painter.begin(&printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
    }

    QSqlQuery   query ;
    qDebug() << query.prepare("select sysdate from dual ");
    if ( query.exec() )
    {

        QString S= QDate::currentDate().toString();
        painter.drawText(850,50,S);
        QPen penred(Qt::black);

        painter.setFont(QFont("Arial", 30));
        penred.setWidth(1);
        painter.setPen(penred);

        QImage imagen(":/imagen/xii.png");
        painter.drawImage(-10,-10,imagen);
        painter.drawText(350,100," Loisir Planning ");
        painter.setFont(QFont("Arial",30));
        painter.setPen(Qt::black);

    }

    QString numloisir,type,lieu,date_loisir,duree,frais;
    QSqlQuery   qry ;
    int i =50;
    int k=0;
    qDebug() << qry.prepare("select * from LOIS ");

    if ( qry.exec() )
    {

        while(qry.next())
        {

            if ( k % 13 ==0)
            {   i=250;
                painter.setFont(QFont("Arial",10));
                QPen penblack(Qt::black);

                painter.setPen(penblack);
painter.drawText (0,200,"NumLoisir");
painter.drawText (90,200,"TypeLoisir");
painter.drawText (230,200,"Destination");
painter.drawText (420,200,"Date");
painter.drawText (530,200,"Duree");

            }

            painter.setFont(QFont("Arial",10));
            QPen penblack(Qt::black);

            painter.setPen(penblack);
            int j=0;
            numloisir= qry.value(0).toString();
            painter.drawText(j*20,i, numloisir);
            j++;
            type=qry.value(1).toString();
            painter.drawText(j*90,i, type);
            j++;
           lieu=qry.value(2).toString();
            painter.drawText(j*100,i, lieu);
            j++;
            date_loisir=qry.value(3).toString();
            painter.drawText(j*139,i, date_loisir);
            j++;
           duree=qry.value(4).toString();
            painter.drawText(j*140,i, duree);
            j++;
           frais=qry.value(5).toString();
             painter.drawText(j*140,i, frais);


            i+=80;
            k++;

        }
    }

    painter.end();
}

void LoisirDevoir::on_DvExl_clicked()
{
    QTableView *table;
           table = ui->tablumiere;

           QString filters("CSV files (.csv);;All files (.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
           }
}


void LoisirDevoir::on_LoisXl_clicked()
{
    QTableView *table;
           table = ui->tabcamera;

           QString filters("CSV files (.csv);;All files (.*)");
           QString defaultFilter("CSV files (*.csv)");
           QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                              filters, &defaultFilter);
           QFile file(fileName);

           QAbstractItemModel *model =  table->model();
           if (file.open(QFile::WriteOnly | QFile::Truncate)) {
               QTextStream data(&file);
               QStringList strList;
               for (int i = 0; i < model->columnCount(); i++) {
                   if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                       strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                   else
                       strList.append("");
               }
               data << strList.join(";") << "\n";
               for (int i = 0; i < model->rowCount(); i++) {
                   strList.clear();
                   for (int j = 0; j < model->columnCount(); j++) {

                       if (model->data(model->index(i, j)).toString().length() > 0)
                           strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") + "\n";
               }
               file.close();
               QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
           }
}



void LoisirDevoir::on_buttonAjoutercamera_clicked()
{
    int num=ui->idcam->value();
    QString etat=ui->etatcam->currentText();

    QString Dimensions=ui->emplacementcam->text();

    Camera l(num,etat,Dimensions);
    QMessageBox msg;
    if(l.ajouter())
    {
        msg.setText("ajout avec succés");
        //show_tables(p.afficherProduit(),ui->tabProduits);
        proxy2 = new QSortFilterProxyModel();
        proxy2->setSourceModel(l.afficher());
        ui->tabcamera->setModel(proxy2);
        ui->idcam->clear();

        ui->emplacementcam->clear();

    }
    else
    {
        msg.setText("echec lors de l'ajout");
    }
    msg.exec();
}

void LoisirDevoir::on_buttonModiferercamera_clicked()
{
    int num=ui->idcam->value();
    QString etat=ui->etatcam->currentText();

    QString Dimensions=ui->emplacementcam->text();

    Camera l(num,etat,Dimensions);

 bool test=l.modifier();
 QMessageBox msg;
 if(test)
 {
     msg.setText("modifier avec succés");
     proxy2 = new QSortFilterProxyModel();
     proxy2->setSourceModel(l.afficher());
     ui->tabcamera->setModel(proxy2);
 }
 else
 {
     msg.setText("echec lors du modification");
 }
 msg.exec();


}

void LoisirDevoir::on_buttonSupprimercamera_clicked()
{
    Camera l;
    QMessageBox msgBox;
    QMessageBox msg;
    if(loisirSelectionne=="")
    {
         msgBox.setText("Aucune Loisir n'est selectionné!");
    }
    else
    {
        msgBox.setText("Voulez vous supprimer le Loisir "
                       "numéro "+loisirSelectionne+" ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    }

    int rep=msgBox.exec();
    switch(rep)
    {
          case QMessageBox::Yes:

            if (l.supprimer(loisirSelectionne.toInt()))
            {
            msg.setText("suppression avec succes.");
            msg.setIcon(QMessageBox::Information);
            proxy2 = new QSortFilterProxyModel();
            proxy2->setSourceModel(l.afficher());
            ui->tabcamera->setModel(proxy2);

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

void LoisirDevoir::on_tabcamera_doubleClicked(const QModelIndex &index)
{
    QSqlQuery query;
   query.prepare("select * from CAMERA where IDCAM= :idcam");
   query.bindValue(":idcam",loisirSelectionne);
   if(query.exec())
   {
       while(query.next())
       {

           ui->idcam->setValue(query.value(0).toInt());
           ui->etatcam->setCurrentIndex(0);
           ui->etatcam->setCurrentIndex(ui->etatcam->findText(query.value(1).toString(),Qt::MatchExactly));
           ui->emplacementcam->setText(query.value(2).toString());


       }
   }

}

void LoisirDevoir::on_tabcamera_clicked(const QModelIndex &index)
{
    loisirSelectionne=ui->tabcamera->model()->data(index.sibling(index.row(),0)).toString();
    Camera l;
    l.setidcam(loisirSelectionne.toInt());
}
