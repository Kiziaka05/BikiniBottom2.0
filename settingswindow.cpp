#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
  //  this->setStyleSheet("background-color: white; text-color: black");
 //   ui->btn_close->setStyleSheet("background-color: red; color: white;");

}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_btn_close_clicked()
{
    this->close();
}
void SettingsWindow::on_sld_volume_value_Changed(int value)
{
   // player->setVolume(value); // значення від 0 до 100
}
