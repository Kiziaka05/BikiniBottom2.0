#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QList>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    void SetCurrentRadius(int Radius);

signals:
    void MapRadChanged(int NewRad);
    void VolumeChanged(int volume);

private:
    Ui::SettingsWindow *ui;

    const QList<int> MapRads = {10, 15, 20};
    const QList<QString> MapSizeNames = {"Small", "Medium", "Big"};

    void UpdateMapSizeLabel(int sliderValue);

private slots:
    void on_btn_close_clicked();
    void on_sld_volume_value_Changed(int value);
    void on_slider_mapsize_valueChanged(int sliderValue);
};

#endif // SETTINGSWINDOW_H
