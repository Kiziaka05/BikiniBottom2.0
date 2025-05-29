#ifndef NEW_OR_OLD_GAME_H
#define NEW_OR_OLD_GAME_H

#include <QDialog>

namespace Ui {
class New_or_old_Game;
}

class New_or_old_Game : public QDialog
{
    Q_OBJECT

public:
    explicit New_or_old_Game(QWidget *parent = nullptr);
    ~New_or_old_Game();

public slots:
    void on_btn_newGame_clicked();
    void on_btn_loadGame_clicked();
signals:
    void startNewGame();
    void loadGame();

private:
    Ui::New_or_old_Game *ui;
};


#endif // NEW_OR_OLD_GAME_H
