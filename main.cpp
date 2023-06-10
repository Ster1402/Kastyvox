#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include "fenetre.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
        translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        app.installTranslator(&translator);

    Fenetre fen;

    app.setStyleSheet ("QMenu {font-size: 15px; color: #202020} "
    "QLabel#tA, QLabel#tS, QLabel#tC, QLabel#tB { border: 1px solid black; font-weight: bold; color: maroon; font-size: 25px; font-family: Arial; padding: 5px; }"
    "QListView{ border: 1px solid black; font-weight: bold; background: #DFE; font-size: 18px; padding: 5 }"
    "*{ font-size: 14px } "
    "QListView#normal{ font-weight: normal; font-family : Arial; color: #181818} "
    "QTextEdit { font-size : 19px;  background: #DFD; color: maroon; }"
    "QLineEdit,QSpinBox,QDateEdit { color: #201818; } "
     "QLineEdit:hover,QLineEdit:focus, QSpinBox:hover,QDateEdit:focus,QDateEdit:hover,QSpinBox:focus {  background : #DFD; border: 1px solid #171717; color: #191313 ; font-size: 20px; font-weight : bold; }");

    fen.show ();

    return app.exec ();
}

