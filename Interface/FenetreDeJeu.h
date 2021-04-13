#pragma once

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
#include <QLCDNumber>
#include "Board.h"
#include "FenetrePointage.h"

class FenetreDeJeu : public QWidget
{
    Q_OBJECT

public:
    FenetreDeJeu(QMainWindow* fenetrePrincipale, FenetrePointage* fenetrePointage, Player* playerPrincipal);
    ~FenetreDeJeu();
    void boardInit();


private:
    // layout
    Board* board;

   QMenuBar* m_menuBar;
   QMenu *m_menuMenu;
   QAction *m_menuOptionAccueil;
   QAction *m_menuOptionQuitter;
   QMenu* m_menuAide;

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

   QVBoxLayout* m_layoutGauche;
   QGridLayout* m_layoutProgressBar;
   QVBoxLayout* m_layoutScore;
   QLabel* m_Garder;
   QLabel* m_Test;
   QLabel* m_score;
   QLabel* m_bestscore;
   QLabel* m_joueur;
   QLabel* m_level;
   QLabel* m_nextLevel;
   QGridLayout* m_hold;
   QVBoxLayout* m_tetris;
   QGridLayout* m_pnext;
   QVBoxLayout* m_layoutCentre;
   QVBoxLayout* m_layoutDroite;
   QProgressBar* m_bar;
   QProgressBar* m_elevel;
   QLCDNumber* m_lcdScore;

   FenetrePointage* m_fenetrePointage;
   Player* player;

public slots:
    void slotPourFenetrePrincipale();
    void updateScore();
    void updateLevel();
    void slotGameOver();

signals:
    void signalRetourPrincipale();
};
#endif