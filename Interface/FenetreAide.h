#pragma once
#ifndef FENETREAIDE_H
#define FENETREAIDE_H



#include <QMainWindow>
#include <QMenu>
#include <QApplication>
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
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QProgressBar>


class FenetreAide : public QWidget
{

    Q_OBJECT

public:
    FenetreAide(QMainWindow* fenetrePrincipale);
    ~FenetreAide();


private:
    QVBoxLayout* m_layoutAide;
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* label4;


};
#endif