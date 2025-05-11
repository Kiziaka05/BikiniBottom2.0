#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingswindow.h"
#include "HexWidget.h"

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

private slots:
    void on_btn_exit_clicked();
    void on_btn_settings_clicked();
    void on_btn_play_clicked();
};
#endif // MAINWINDOW_H
