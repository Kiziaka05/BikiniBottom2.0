#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QLabel>
#include <QSlider>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    //стилі
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setFixedSize( 550, 420 );

    this->setStyleSheet(
        "SettingsWindow {"
        "    background-image: url(TestBackground.png);"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    background-attachment: fixed;"
        "    border-image: url(TestBackground.png) 0 0 0 0 stretch stretch;"
        "}"



        );
    //

    if(ui->slider_mapsize)
    {
        ui->slider_mapsize->setMinimum(0);
        ui->slider_mapsize->setMaximum(MapRads.size() - 1);
        ui->slider_mapsize->setTickInterval(1);
    }
    connect(ui->sld_volume,&QSlider::valueChanged, this, &SettingsWindow::on_sld_volume_value_Changed);
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
    emit VolumeChanged(value);
}

void SettingsWindow::UpdateMapSizeLabel(int sliderValue)
{
    if(ui->labelCurrentMapSizeName && sliderValue >= 0 && sliderValue < MapSizeNames.size())
        ui->labelCurrentMapSizeName->setText(MapSizeNames.at(sliderValue));
}

void SettingsWindow::SetCurrentRadius(int Radius)
{
    int sliderValue = MapRads.indexOf(Radius);
    if(sliderValue == -1)
        sliderValue = 1;

    if(ui->slider_mapsize)
    {
        bool OldSignalState = ui->slider_mapsize->blockSignals(true);
        ui->slider_mapsize->setValue(sliderValue);
        ui->slider_mapsize->blockSignals(OldSignalState);
    }
    UpdateMapSizeLabel(sliderValue);
}

void SettingsWindow::on_slider_mapsize_valueChanged(int sliderValue)
{
    if(sliderValue >= 0 && sliderValue < MapRads.size())
    {
        int ActualRadius = MapRads.at(sliderValue);
        emit MapRadChanged(ActualRadius);
        UpdateMapSizeLabel(sliderValue);
    }
}
