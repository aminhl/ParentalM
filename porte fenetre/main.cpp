#include "mainwindow.h"
#include "connexion.h"
#include <QMessageBox>
#include <QTextToSpeech>
#include <QApplication>
#include <QFile>


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        Connexion c;
        bool test=c.ouvrirConnexion();
        MainWindow w;
        //open qss file
        QFile File("C://projet-new//Toolery.qss");
                File.open(QFile::ReadOnly);
                QString StyleSheet =QLatin1String(File.readAll());
                //setup stylesheet
                a.setStyleSheet(StyleSheet);
        //setup stylesheet
        a.setStyleSheet(StyleSheet);

        QTextToSpeech * m_speech =new QTextToSpeech();
        if(test)
        {
            w.show();

           m_speech->say("database is opened successfully");
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click ok to exit."), QMessageBox::Close);


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click ok to exit."), QMessageBox::Close);
            m_speech->say("database is opened successfully");

        }


    return a.exec();
}
