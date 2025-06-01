#ifndef HEROWIDGET_H
#define HEROWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDialog>
#include <QPixmap>
#include <QListWidget>
#include "HexWidget.h"
class MainHero;

namespace Ui {
class HeroWidget;
}

class HeroWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeroWidget(const QPixmap& Hero, HexWidget* mappa, QWidget *parent = nullptr);
    ~HeroWidget();
    void Update_stats();

private:
    Ui::HeroWidget *ui;
    HexWidget* Mappa = NULL;
    QPixmap HeroTexture;
    void displayStats();
};

#endif // HEROWIDGET_H
