#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingswindow.h"
#include "HexWidget.h"
#include "Pause.h"
QT_BEGIN_NAMESPACE
namespace Ui {
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

private slots:
    void on_btn_exit_clicked();
    void on_btn_settings_clicked();
    void on_btn_play_clicked();
    void on_btn_pause_clicked();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
