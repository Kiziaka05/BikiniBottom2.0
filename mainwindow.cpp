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
    MapRadius(10),
    heroWidget(nullptr)
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
    delete settingsWindow;
    delete heroWidget;
}


//радіус гри
void MainWindow::HandleMapRadiusChanged(int NewRadius)
{
    if(NewRadius > 0)
        MapRadius = NewRadius;
}

//кнопка виходу
void MainWindow::on_btn_exit_clicked()
{
    this->close();
}

//кнопка налаштування
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


//кнопка гри
void MainWindow::on_btn_play_clicked()
{
    New_or_old_Game *chooseDialog = new New_or_old_Game(this);

    connect(chooseDialog, &New_or_old_Game::startNewGame, this, [=]() {
        if (MapWidget)
        {
            MapWidget->deleteLater();
            MapWidget = nullptr;
        }

        if (heroWidget) {
            heroWidget->hide();
            heroWidget->deleteLater();
            heroWidget = nullptr;
        }


        MapWidget = new HexWidget(MapRadius, this);

        connect(MapWidget, &HexWidget::gameOver, this, &MainWindow::HandleGameOver);
        connect(MapWidget, &HexWidget::victory, this, &MainWindow::HandleVictory);

        if (MenuWidget) {
            MenuWidget->hide();
        } else {
            qCritical("MainWindow::startNewGame - MenuWidget is null! Cannot hide. Aborting game start.");

            if(MapWidget) { delete MapWidget; MapWidget = nullptr; }
            QApplication::quit();
            return;
        }
        setCentralWidget(MapWidget);
        MapWidget->setFocus();

        QPixmap HeroTexture("NPC5Texture.png");
        if (!HeroTexture.isNull()) {
            heroWidget = new HeroWidget(HeroTexture, MapWidget, this); // MainWindow як батько
            heroWidget->setFixedSize(200, 100);
            int x = 10;
            int y = height() - heroWidget->height() - 10;
            heroWidget->move(x, y);
            heroWidget->raise();
            heroWidget->show();

            connect(MapWidget, &HexWidget::heroStatsChanged,
                    heroWidget, &HeroWidget::Update_stats);
        } else {
            qWarning("Failed to load HeroTexture for HeroWidget.");
        }

    });

    connect(chooseDialog, &New_or_old_Game::loadGame, this, [=]() {
        if(MapWidget)
        {
            if(MenuWidget && MenuWidget->isVisible())
            {
                MapWidget->deleteLater();
                MapWidget = nullptr;
            }
            else if (!MenuWidget || !MenuWidget->isVisible()) {

                MapWidget->deleteLater();
                MapWidget = nullptr;
            }
        }

        if (heroWidget) {
            heroWidget->hide();
            heroWidget->deleteLater();
            heroWidget = nullptr;
        }

        if (!MapWidget)
        {
            MapWidget = new HexWidget(MapRadius, this);
        }

        connect(MapWidget, &HexWidget::gameOver, this, &MainWindow::HandleGameOver);
        connect(MapWidget, &HexWidget::victory, this, &MainWindow::HandleVictory);

        // Завантажуємо карту
        if (!MapWidget->LoadMapFromFile("map.dat")) {
            QMessageBox::warning(this, tr("Помилка завантаження"), tr("Не вдалося завантажити карту."));
            if(MapWidget) { // Очищаємо MapWidget, якщо він був створений, але завантаження не вдалося
                if (centralWidget() == MapWidget) takeCentralWidget();
                MapWidget->deleteLater();
                MapWidget = nullptr;
            }
            if (MenuWidget) { // Повертаємо меню
                if (centralWidget() != MenuWidget) setCentralWidget(MenuWidget);
                MenuWidget->show();
            } else {
                qCritical("MainWindow::loadGame - MenuWidget is null after failed load!");
                QApplication::quit();
            }
            return;
        }

        if (!MenuWidget) {
            MenuWidget = takeCentralWidget();
        }

        if (MenuWidget) { // Перевірка MenuWidget
            MenuWidget->hide();
        } else {
            qCritical("MainWindow::loadGame - MenuWidget is null! Cannot hide.");
            if(MapWidget) { if(centralWidget() == MapWidget) takeCentralWidget(); MapWidget->deleteLater(); MapWidget = nullptr; }
            QApplication::quit();
            return;
        }
        setCentralWidget(MapWidget);
        MapWidget->setFocus();


        QPixmap HeroTexture("NPC5Texture.png");
        if (!HeroTexture.isNull()) {
            heroWidget = new HeroWidget(HeroTexture, MapWidget, this);
            heroWidget->setFixedSize(200, 100);
            int x = 10;
            int y = height() - heroWidget->height() - 10;
            heroWidget->move(x, y);
            heroWidget->raise();
            heroWidget->show();
            connect(MapWidget, &HexWidget::heroStatsChanged,
                    heroWidget, &HeroWidget::Update_stats);
        } else {
            qWarning("Failed to load HeroTexture for HeroWidget in loadGame.");
        }

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

//кнопка паузи
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

//подія програшу
void MainWindow::HandleGameOver()
{

    QMessageBox::information(this, tr("Гру завершено"), tr("Ви програли!"));


    if (heroWidget) {
        heroWidget->hide();
        heroWidget->deleteLater();
        heroWidget = nullptr;
    }

    if (MapWidget) {
        if (centralWidget() == MapWidget) {
            takeCentralWidget();
        }
        MapWidget->deleteLater();
        MapWidget = nullptr;
    }

    if (MenuWidget) {
        setCentralWidget(MenuWidget);
        MenuWidget->show();
    } else {
        qCritical("MainWindow::HandleGameOver: MenuWidget is null! Cannot return to menu.");
        QApplication::quit();
    }
}

//подія перемоги
void MainWindow::HandleVictory()
{
    qDebug() << "Victory handled in MainWindow. Returning to menu.";

    if (MapWidget) {

        if (centralWidget() == MapWidget) {
            takeCentralWidget();
        }
        MapWidget->deleteLater();
        MapWidget = nullptr;
    }



     if (heroWidget) {
         heroWidget->hide();
         heroWidget->deleteLater();
         heroWidget = nullptr;
     }

    if (MenuWidget) {
        setCentralWidget(MenuWidget);
        MenuWidget->show();
    } else {
        qCritical("MainWindow::HandleVictory: MenuWidget is null! Cannot return to menu.");
        QApplication::quit();
    }
}

