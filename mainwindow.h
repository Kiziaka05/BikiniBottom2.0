#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingswindow.h"
#include "HexWidget.h"
#include "Pause.h"
#include "herowidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class HeroWidget;
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SettingsWindow *settingsWindow;
    QWidget* MenuWidget=nullptr;
    HexWidget* MapWidget=nullptr;
    Pause* pauseDialog=nullptr;
    HeroWidget* heroWidget = nullptr;

    int MapRadius = 10;

private slots:
    void on_btn_exit_clicked();
    void on_btn_settings_clicked();
    void on_btn_play_clicked();
    void on_btn_pause_clicked();

    void HandleMapRadiusChanged(int NewRadius);
    void HandleGameOver();
    void HandleVictory();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
