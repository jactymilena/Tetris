TEMPLATE = vcapp
TARGET = tetris
HEADERS += FenetrePrincipale.h FenetreDeJeu.h FenetrePointage.h Player.h
SOURCES  += main.cpp FenetreDeJeu.cpp FenetrePrincipale.cpp FenetrePointage.cpp Player.cpp
CONFIG  += warn_on qt debug windows console
QT += widgets
