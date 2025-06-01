#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include "new_or_old_game.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    settingsWindow(nullptr),
    MapRadius(10)
{
    ui->setupUi(this);

    //стилі

    this->setFixedSize( 1280, 720 );
    QIcon mainWindowIcon("icon.png");
    this->setWindowIcon(mainWindowIcon);
    this->setStyleSheet(
        "QMainWindow {"
        "    background-image: url(background.png);"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    background-attachment: fixed;"
        "    border-image: url(background.png) 0 0 0 0 stretch stretch;"
        "}"


        );
    //


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

void MainWindow::HandleMapRadiusChanged(int NewRadius)
{
    if(NewRadius > 0)
        MapRadius = NewRadius;
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}

void MainWindow::on_btn_settings_clicked()
{
    if(!settingsWindow)
    {
        settingsWindow = new SettingsWindow();
        connect(settingsWindow, &SettingsWindow::MapRadChanged,
                this, &MainWindow::HandleMapRadiusChanged);
    }

    settingsWindow->SetCurrentRadius(MapRadius);
    settingsWindow->show();
    settingsWindow->activateWindow();
}

void MainWindow::on_btn_play_clicked()
{
    New_or_old_Game *chooseDialog = new New_or_old_Game(this);

    connect(chooseDialog, &New_or_old_Game::startNewGame, this, [=]() {
        if (MapWidget)
        {
            delete MapWidget;
            MapWidget = nullptr;
        }
        MapWidget = new HexWidget(MapRadius, this);

        connect(MapWidget, &HexWidget::gameOver, this, &MainWindow::HandleGameOver);

        if (!MenuWidget)
            MenuWidget = takeCentralWidget();

        MenuWidget->hide();
        setCentralWidget(MapWidget);
        MapWidget->setFocus();

        if (!heroWidget)
        {
            QPixmap HeroTexture("NPC5Texture.png");
            heroWidget = new HeroWidget(HeroTexture, MapWidget, this);
            heroWidget->setFixedSize(200, 100);
            heroWidget->setParent(this);
            int x = 10;
            int y = height() - heroWidget->height() - 10;
            heroWidget->move(x, y);
            heroWidget->raise();
            heroWidget->show();
        }
        connect(MapWidget, &HexWidget::heroStatsChanged,
                heroWidget, &HeroWidget::Update_stats);
    });

    connect(chooseDialog, &New_or_old_Game::loadGame, this, [=]() {
        if(MapWidget)
        {
            if(MenuWidget && MenuWidget->isVisible())
            {
                delete MapWidget;
                MapWidget = nullptr;
            }
        }
        if (!MapWidget)
        {
            MapWidget = new HexWidget(MapRadius, this);
        }

        connect(MapWidget, &HexWidget::gameOver, this, &MainWindow::HandleGameOver);

        MapWidget->LoadMapFromFile("map.dat");

        if (!MenuWidget)
            MenuWidget = takeCentralWidget();

        MenuWidget->hide();
        setCentralWidget(MapWidget);
        MapWidget->setFocus();
        if (!heroWidget)
        {
            QPixmap HeroTexture("NPC5Texture.png");
            heroWidget = new HeroWidget(HeroTexture, MapWidget, this);
            heroWidget->setFixedSize(200, 100);
            heroWidget->setParent(this);
            int x = 10;
            int y = height() - heroWidget->height() - 10;
            heroWidget->move(x, y);
            heroWidget->raise();
            heroWidget->show();
        }
        connect(MapWidget, &HexWidget::heroStatsChanged,
                heroWidget, &HeroWidget::Update_stats);
    });

    chooseDialog->exec();
    delete chooseDialog;
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

void MainWindow::HandleGameOver()
{

    QMessageBox::information(this, tr("Гру завершено"), tr("Ви програли!"));


    if (MapWidget) {
        QWidget* oldCentralWidget = takeCentralWidget();
        if (oldCentralWidget == MapWidget) {
            delete MapWidget;
            MapWidget = nullptr;
        } else if (oldCentralWidget) {

            oldCentralWidget->deleteLater();
            if (MapWidget) {
                MapWidget->hide();
                MapWidget->deleteLater();
                MapWidget = nullptr;
            }
        }
    }

    if (MenuWidget) {
        setCentralWidget(MenuWidget);
        MenuWidget->show();
    } else {


        qCritical("MainWindow::HandleGameOver: MenuWidget is null! Cannot return to menu.");
        QApplication::quit();
    }
}
