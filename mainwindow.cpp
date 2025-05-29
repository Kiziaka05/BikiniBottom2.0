#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QKeyEvent>
#include "new_or_old_game.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet(
        "background-image: url(background.png);"
        "background-repeat: no-repeat;"
        "background-position: center;"
        "background-attachment: fixed;"
        "background-size: cover;"
        );

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
    New_or_old_Game *chooseDialog = new New_or_old_Game(this);

    connect(chooseDialog, &New_or_old_Game::startNewGame, this, [=]() {
        if (!MapWidget)
            MapWidget = new HexWidget(this);
        if (!MenuWidget)
            MenuWidget = takeCentralWidget();

        MenuWidget->hide();
        setCentralWidget(MapWidget);
        MapWidget->setFocus();
    });

    connect(chooseDialog, &New_or_old_Game::loadGame, this, [=]() {
        if (!MapWidget)
            MapWidget = new HexWidget(this);

        MapWidget->LoadMapFromFile("map.dat"); // Завантаження карти з файлу

        if (!MenuWidget)
            MenuWidget = takeCentralWidget();

        MenuWidget->hide();
        setCentralWidget(MapWidget);
        MapWidget->setFocus();
    });

    chooseDialog->exec();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        on_btn_pause_clicked();
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::on_btn_pause_clicked()
{
    if (!MapWidget || !MapWidget->isVisible())
    {
        return;
    }
    if (!pauseDialog)
    {
        pauseDialog = new Pause(this, MapWidget);
    }

    int result = pauseDialog->exec();
    if (result != QDialog::Accepted)
    {
        QApplication::quit();
    }
}
