#pragma once

#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include "FenetreDeJeu.h"
#include "FenetrePointage.h"
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
#include <QInputDialog>
#include <QStackedWidget>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
public:
    FenetrePrincipale();
    ~FenetrePrincipale();

public slots:
    void slotPourFenetreDeJeu();
    void slotPourFenetrePointage();
    void slotPourEnableFenetre();

    void closeEvent(QCloseEvent* event);
    void slotChangerFenetrePrincipale();

 

private:

    //Boutons pour les autres pages
    QPushButton* boutonPourFenetreJeu;
    QPushButton* boutonPourFenetreReglage;
    QPushButton* boutonPourScore;

    //Le titre Tetris Mania 
    QLabel* labelTetris;
    
    //Creation d'un laytout
    QVBoxLayout* layoutVertical1;

    QWidget* widget;

    FenetreDeJeu* fenetreDeJeu;
    FenetrePointage* fenetrePointage;
    QInputDialog* demandeUsername;
    QStackedWidget* index;
};
#endif