#pragma once
/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: FenetreDeJeu.h
Date:           15 avril 2021
But:            Déclarer FenetreDeJeu.h
====================================*/

#ifndef FENETREDEJEU_H
#define FENETREDEJEU_H

#include <QMainWindow>
#include <QMenu>
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QProgressBar>
#include <QDebug>
#include <QLCDNumber>
#include "Board.h"
#include "FramePourPiece.h"
#include "FenetrePointage.h"

class FenetreDeJeu : public QWidget
{
    Q_OBJECT

public:
    FenetreDeJeu(QMainWindow* fenetrePrincipale, Player* playerPrincipal);
    ~FenetreDeJeu();
    void boardInit();
    void setUsernameLabel();

private:
    // layout
   Board* board;

   QMenuBar* m_menuBar;
   QMenu *m_menuMenu;
   QAction *m_menuOptionAccueil;
   QAction *m_menuOptionQuitter;
   QAction* m_menuOptionAide;

   QWidget* m_widget;
   QHBoxLayout* m_layout;
 
   QGroupBox* m_gauche; 
   QGroupBox* m_gaucheHold;
   QGroupBox* m_console;
   QGroupBox* m_centre;
   QGroupBox* m_droite;
   QGroupBox* m_holdnext;
   QGroupBox* m_scoreBox;
   QGroupBox* m_progressBarBox;
   QGroupBox* m_nextBestPlayerBox;
   QGroupBox* m_usernameBox;

   QVBoxLayout* m_layoutGauche;
   QVBoxLayout* m_layoutUsername;
   QGridLayout* m_layoutProgressBar;
   QHBoxLayout* m_layoutScore;
   QVBoxLayout* m_layoutBestPlayer;
   QLabel* m_usernameTitle;
   QLabel* m_usernameLabel;
   QLabel* m_holdLabel;
   QLabel* m_nextLabel;
   QLabel* m_score;
   QLabel* m_bestscore;
   QLabel* m_joueur;
   QLabel* m_level;
   QLabel* m_nextLevel;
   QLabel* m_prochainScore;
   QLabel* m_prochainIndividu;
   QGridLayout* m_hold;
   QVBoxLayout* m_tetris;
   QGridLayout* m_pnext;
   QVBoxLayout* m_layoutCentre;
   QVBoxLayout* m_layoutDroite;
   QProgressBar* m_bar;
   QProgressBar* m_elevel;
   FramePourPiece* frameHold;
   FramePourPiece* framePieceSuivante;
   QLCDNumber* m_lcdScore;
   QPixmap* m_userIcon;
   QLabel* m_userIconLabel;

   // Game over widget
   FenetrePointage* m_fenetrePointage;
   QWidget* m_gameOverWidget;
   QVBoxLayout* m_gameOverLayout;
   QPushButton* m_gameOverQuitterButton;
   QPushButton* m_recommencerButton;

   Player* player;
   Player* nextBestPlayer;

public slots:
    void slotPourFenetrePrincipale();
    void updateScore();
    void updateLevel();
    void slotGameOver();
    void recommencerBoard();

    void slotPourTrigeredHold();
    void slotPourTrigeredSuivante();
    void slotPourFenetreAide();
signals:
    void signalRetourPrincipale();
signals:
    void signalAllerAide();
};
#endif