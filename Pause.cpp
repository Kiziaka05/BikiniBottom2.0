#include "Pause.h"
#include "ui_Pause.h"
#include <QApplication>

Pause::Pause(QWidget *parent): QDialog(parent), ui(new Ui::Pause)
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
    QApplication::quit();
}
