TEMPLATE = vcapp
TARGET = tetris
HEADERS += FenetrePrincipale.h FenetreDeJeu.h FenetrePointage.h Player.h Board.h Piece.h FenetreAide.h FramePourPiece.h BoutonPrincipal.h
SOURCES  += main.cpp FenetreDeJeu.cpp FenetrePrincipale.cpp FenetrePointage.cpp Player.cpp Board.cpp Piece.cpp FenetreAide.cpp FramePourPiece.cpp BoutonPrincipal.cpp
CONFIG  += warn_on qt debug windows console
QT += widgets core gui
