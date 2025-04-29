#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
