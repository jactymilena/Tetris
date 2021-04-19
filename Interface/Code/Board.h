#pragma once
/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: Board.h
Date: 9 avril 2021
But: Déclaration de Board.h
====================================*/

#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include <QFrame>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QMouseEvent>
#include <QFontDataBase>
#include <QLabel>
#include <string>
#include <string.h>
#include "Piece.h"
#include "Player.h"
#include "CommunicationFPGA.h"

#define LIGNES 18
#define COLONNES 8

#define ADD 1
#define REMOVE 0
#define DOWN 0
#define SCORE 100

#define HAUTEUR 590
#define LARGEUR 1200/3
#define COTE_CARRE 30

struct Case {
	int value;
	QColor color;
	Case();
};

class Board : public QFrame {
	Q_OBJECT
public:
	Board(QWidget* fenetreJeu, Player* playerPrincipal);
	void startGame();
	void resetBoard();
	bool loadPiece(int num_piece);
	void pieceState(int state);
	bool verifMove(int direction);
	bool verifLigne();
	void enleverLigne(int i);
	void restart();
	void pause(bool cond); // si cond true, reste dans la fenetre, sinon retourne a l'accueil
	void setModeFPGA(bool mode);
	bool getModeFPGA();

	//Menu Score
	void augmenterScore(int nbLigne);
	void augmenterLevel();

	// Mouvement piece
	void movePiece(int direction);

	//Menu hold
	void changerPiece();

	//Getter Pieces
	bool getIsStarted();
	Piece getPieceHold();
	Piece getPieceSuivante();
protected:
	void paintEvent(QPaintEvent* event);
	void keyPressEvent(QKeyEvent* event);
	//void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent* event);

public slots:
	void moveDownPiece();
	void lireFPGA();

signals:
	void declencherHold();
	void declencherSuivante();
	void gameOverSignal();

private:
	Case cases[LIGNES][COLONNES];
	bool game_over;
	bool nouvellePiece;
	Piece pieceHold;
	Piece piece;
	Piece pieceApres;
	int difficulte;
	Player* player;
	bool modeFPGA;

	// Qt
	QGridLayout* layout;
	QTimer* timer;
	QTimer* timerFPGA;
	bool isPaused;
	bool isStarted;
	QWidget *fenetre;

};
