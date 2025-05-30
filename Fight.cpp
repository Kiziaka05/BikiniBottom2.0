#include "Fight.h"
#include "ui_Fight.h"

Fight::Fight(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Fight)
{
    ui->setupUi(this);
}

Fight::~Fight()
{
    delete ui;
}
