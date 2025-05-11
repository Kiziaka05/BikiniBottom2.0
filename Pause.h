#ifndef PAUSE_H
#define PAUSE_H

#include <QDialog>

namespace Ui {
class Pause;
}

class Pause : public QDialog
{
    Q_OBJECT

public:
    explicit Pause(QWidget *parent = nullptr);
    ~Pause();

private:
    Ui::Pause *ui;

private slots:
    void on_Continue_clicked();
    void on_Exit_clicked();
};

#endif // PAUSE_H
