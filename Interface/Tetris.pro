TEMPLATE = vcapp
TARGET = tetris
HEADERS += FenetrePrincipale.h FenetreDeJeu.h Player.h Board.h Piece.h FenetrePointage.h
SOURCES  += main.cpp FenetreDeJeu.cpp FenetrePrincipale.cpp Player.cpp Board.cpp Piece.cpp FenetrePointage.cpp
CONFIG  += warn_on qt debug windows console
QT += widgets
