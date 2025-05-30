#ifndef FIGHT_H
#define FIGHT_H

#include <QDialog>

namespace Ui {
class Fight;
}

class Fight : public QDialog
{
    Q_OBJECT

public:
    explicit Fight(QWidget *parent = nullptr);
    ~Fight();

private:
    Ui::Fight *ui;
};

#endif // FIGHT_H
