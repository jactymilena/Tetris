#pragma once

#ifndef FENETREDEJEU_H
#define FENETREDEJEU_H

#include <QMainWindow>
#include <QMenu>
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
#include <QGridLayout>
#include "Board.h"

class FenetreDeJeu : public QWidget
{
    Q_OBJECT
public:
    FenetreDeJeu();
    ~FenetreDeJeu();
    void boardInit();


private:
    // layout
    Board* board;

    QLabel* labelDeJeu;
    QLabel* labelDeJeu2;

    QHBoxLayout* layout;
};
#endif