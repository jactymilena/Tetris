#pragma once

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "FenetreDeJeu.h"
#include "FenetrePointage.h"
#include "Player.h"
#include "FenetreAide.h"
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
#include <QStackedWidget>
#include <QInputDialog>
#include "BoutonPrincipal.h"
#include "Player.h"

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
public:
    FenetrePrincipale();
    ~FenetrePrincipale();

public slots:
    void slotPourFenetreDeJeu();
    void slotChangerFenetrePrincipale();
    void slotPourFenetrePointage();
    void slotPourEnableFenetre();
    void slotChangerFenetreAide();
    void closeEvent(QCloseEvent* event);

private:
    //Boutons pour les autres pages
    BoutonPrincipal* boutonPourFenetreJeu;
    BoutonPrincipal* boutonPourFenetreReglage;
    BoutonPrincipal* boutonPourScore;

    //Le titre Tetris Mania 
    QLabel* labelTetris;
    
    //Creation d'un laytout
    QVBoxLayout* layoutVertical1;

    QWidget* widget;

    FenetreDeJeu* fenetreDeJeu;
    FenetreAide* fenetreAide;
    QStackedWidget* index;

    //Pointage
    FenetrePointage* fenetrePointage;
    QInputDialog* demandeUsername;

    //Reglage 



    //Player
    Player* player;
};
#endif