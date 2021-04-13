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
#include "Board.h"
#include "FramePourPiece.h"

class FenetreDeJeu : public QWidget
{
    Q_OBJECT

public:
    FenetreDeJeu(QMainWindow* fenetrePrincipale);
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

   QVBoxLayout* m_layoutGauche;
   QLabel* m_Garder;
   QLabel* m_Test;
   QLabel* m_next;
   QLabel* m_score;
   QLabel* m_bestscore;
   QLabel* m_joueur;
   QLabel* m_level;
   QGridLayout* m_hold;
   QVBoxLayout* m_tetris;
   QGridLayout* m_pnext;
   QVBoxLayout* m_layoutCentre;
   QVBoxLayout* m_layoutDroite;
   QProgressBar* m_bar;
   QProgressBar* m_elevel;
   FramePourPiece* frameHold;
   FramePourPiece* framePieceSuivante;



public slots:
    void slotPourFenetrePrincipale();
    void slotPourTrigeredHold();
    void slotPourTrigeredSuivante();
signals:
    void signalRetourPrincipale();
};
#endif