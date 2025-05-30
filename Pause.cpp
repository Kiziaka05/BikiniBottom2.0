#include "Pause.h"
#include "ui_Pause.h"
#include <QApplication>

Pause::Pause(QWidget *parent, HexWidget *widget): QDialog(parent), ui(new Ui::Pause), hexWidget(widget)
{
    ui->setupUi(this);
}

Pause::~Pause()
{
    delete ui;
}

void Pause::on_Continue_clicked()
{
    accept();
}

void Pause::on_Exit_clicked()
{
    if(hexWidget)
    {
    hexWidget->SaveMapToFile("map.dat");
    }
    QApplication::quit();
}
