#pragma once

#ifndef FENETREPOINTAGE_H
#define FENETREPOINTAGE_H

#include <QMainWindow>
#include <QMenu>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMenuBar>
#include <QGroupBox>
#include <string>
#include <QDebug>
#include <QWidget>
#include <QObject>
#include "Player.h"
class FenetrePointage : public QWidget
{
    Q_OBJECT
public:
    FenetrePointage(QObject* fenetreArrivante, Player* playerPrincipal);
    FenetrePointage(Player* playerPrincipal);
    ~FenetrePointage();

    void fenetreInit(Player* player);

    void setJoueurUsername();
    void loadHighscore();
    void checkerScore();
    void closeEvent(QCloseEvent* event);
    void getNextBestScore();

public slots:
    void updateScore();

signals:
    void signalClosingFenetrePointage();

private:
    QVBoxLayout* layout;

    //Pour Joueur
    QLabel* usernameTitre;
    QLabel* positionTitreJoueur;
    QLabel* highscoreTitre;
    QLabel* scoreJoueur;
    QLabel* nomJoueur;
    QLabel* votreScore;
    QLabel* positionJoueur;

    //Pour table de score
    QLabel* highscore;
    QLabel* positionTitre;
    QLabel* scoreTitre;
    QLabel* nomTitre;

    QLabel** position;
    QLabel** name;
    QLabel** score;

    QPushButton* retourPagePrincipale;

    QGroupBox* groupBoxScore;
    QGroupBox* groupBoxUser;
    QGridLayout* gridScore;
    QGridLayout* gridScoreUser;
    std::vector<Player*> historique;

    Player* player;

};
#endif
