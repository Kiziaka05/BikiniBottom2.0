#include "new_or_old_game.h"
#include "ui_new_or_old_game.h"

New_or_old_Game::New_or_old_Game(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::New_or_old_Game)
{
    ui->setupUi(this);
    connect(ui->LoadGame, &QPushButton::clicked, this, &New_or_old_Game::on_btn_loadGame_clicked);
    connect(ui->NewGame, &QPushButton::clicked, this, &New_or_old_Game::on_btn_newGame_clicked);
}

New_or_old_Game::~New_or_old_Game()
{
    delete ui;
}

void New_or_old_Game::on_btn_newGame_clicked()
{
    emit startNewGame();
    accept();
}

void New_or_old_Game::on_btn_loadGame_clicked()
{
    emit loadGame();
    accept();
}
