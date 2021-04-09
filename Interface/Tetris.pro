TEMPLATE = vcapp
TARGET = tetris
HEADERS += FenetrePrincipale.h FenetreDeJeu.h
SOURCES  += main.cpp FenetreDeJeu.cpp FenetrePrincipale.cpp
CONFIG  += warn_on qt debug windows console
QT += widgets
