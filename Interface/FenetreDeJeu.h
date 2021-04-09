#pragma once

#ifndef FENETREDEJEU_H
#define FENETREDEJEU_H

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
class FenetreDeJeu : public QWidget
{
    Q_OBJECT
public:
    FenetreDeJeu();
    ~FenetreDeJeu();
private:
    QMenuBar* menuBar;
    QMenu* menu;

    QLabel* labelDeJeu;

    QVBoxLayout* layoutVerticalFenetreDeJeu;
};
#endif