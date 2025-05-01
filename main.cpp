#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMainWindow>

#include "AI.h"
#include "Cell.h"
#include "Event.h"
#include "GameManager.h"
#include "Map.h"
#include "RenderGame.h"
#include "Unit.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include "HexWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QTranslator translator;
    // const QStringList uiLanguages = QLocale::system().uiLanguages();
    // for (const QString &locale : uiLanguages) {
    //     const QString baseName = "BikiniBottom2_" + QLocale(locale).name();
    //     if (translator.load(":/i18n/" + baseName)) {
    //         a.installTranslator(&translator);
    //         break;
    //     }
    // }
    // MainWindow w;
    // w.show();

    QMainWindow window;
    HexWidget* hexWidget = new HexWidget;

    window.setCentralWidget(hexWidget);
    window.resize(800,600);
    window.show();

    return a.exec();
}
