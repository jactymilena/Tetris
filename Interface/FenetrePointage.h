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
#include "Player.h"
class FenetrePointage : public QWidget
{
    Q_OBJECT
public:
    FenetrePointage(QObject* fenetreArrivante);
    ~FenetrePointage();

    void setJoueurUsername(std::string username);

    void closeEvent(QCloseEvent* event);
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

    Player joueur1;

    QGroupBox* groupBoxScore;
    QGroupBox* groupBoxUser;
    QGridLayout* gridScore;
    QGridLayout* gridScoreUser;
};
#endif