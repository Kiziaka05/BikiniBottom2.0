#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-image: url(background.jpg);");
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);

    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("Sponge.mp3"));
    audioOutput->setVolume(50);
    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}

void MainWindow::on_btn_settings_clicked()
{
    settingsWindow = new SettingsWindow();
    settingsWindow->show();
}

void MainWindow::on_btn_play_clicked()
{
    if(!MapWidget)
        MapWidget= new HexWidget(this);


    if(!MenuWidget)
        MenuWidget= takeCentralWidget();

    MenuWidget->hide();

    setCentralWidget(MapWidget);
    MapWidget->setFocus();


}
