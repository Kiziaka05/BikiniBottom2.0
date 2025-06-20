#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMainWindow>

#include <iostream>
#include <vector>

#include "AI.h"
#include "Cell.h"
#include "Map.h"
#include "Unit.h"
#include "HexWidget.h"
#include "Fight.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    a.setStyleSheet(
        "QMessageBox {"
        "    font-family: 'Unispace';"
        "}"
        "QMessageBox QLabel {"
        "    font-family: 'Unispace';"

        "}"
        "QMessageBox QPushButton {"
        "    font-family: 'Unispace';"
        "}"
        );







     QIcon appIcon("icon.png");
     a.setWindowIcon(appIcon);
     QTranslator translator;
     const QStringList uiLanguages = QLocale::system().uiLanguages();
     for (const QString &locale : uiLanguages) {
         const QString baseName = "BikiniBottom2_" + QLocale(locale).name();
         if (translator.load(":/i18n/" + baseName)) {
             a.installTranslator(&translator);
             break;
         }
     }
     MainWindow w;
     w.show();





    return a.exec();
}
