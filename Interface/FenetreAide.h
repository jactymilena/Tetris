/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: FenetreAide.h
Date: 15 avril 2021
But: Déclarer FenetreAide.h 
====================================*/
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
#include "BoutonPrincipal.h"
#include <QPixMap>
#include <QInputDialog>
#include <QLineEdit>
#include <QSlider>

class FenetreAide : public QWidget
{
    Q_OBJECT

public:
    FenetreAide(QMainWindow* fenetrePrincipale);
    ~FenetreAide();


private:
    QVBoxLayout* m_layoutAide;
    QGridLayout* m_layoutGrid;
    QGridLayout* m_layoutGridSon;
    QVBoxLayout* m_layoutBob;
    QGroupBox* m_group1;
    QGroupBox* m_group2;
    QGroupBox* m_group3;

    QLabel* m_label1;
    QLabel* m_label2;
    QLabel* m_label3;
    QLabel* m_label4;
    QLabel* m_label5;
    QLabel* m_label6;
    QLabel* m_label7;
    QLabel* m_labelson;
    QLabel* m_labelsfx;

    QSlider* m_sons;
    QSlider* m_sfx;

    QLineEdit* m_touche1;
    QLineEdit* m_touche2;
    QLineEdit* m_touche3;
    QLineEdit* m_touche4;
    QLineEdit* m_touche5;
    QLineEdit* m_touche6;
    QLineEdit* m_touche7;

    BoutonPrincipal* boutonPourFenetreRetour;

    QPixmap* m_pixmap1;
    QPixmap* m_pixmap2;
    QPixmap* m_pixmap3;
    QPixmap* m_pixmap4;
    QPixmap* m_pixmap5;
    QPixmap* m_pixmap6;
    QPixmap* m_pixmap7;

public slots:
    void slotPourFenetreRetour();
signals:
    void retourFenetreAvant();

};
#endif