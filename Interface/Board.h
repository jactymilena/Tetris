#pragma once
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
#include "Piece.h"
#include "Player.h"

#define LIGNES 18
#define COLONNES 8

#define ADD 1
#define REMOVE 0
#define DOWN 0
#define SCORE 100

#define HAUTEUR 590
#define LARGEUR 1200/3
#define COTE_CARRE 30

//BOOL statutport = false;            // statut du port de communication qui sera cree
//
//
//int compteur_temps = 0;
//int swt = 0;                         // donnee recue du FPGA
//int aff7sg_octet0 = 0;               // octet 0 (droite) pour afficheur 7 segments
//int aff7sg_octet1 = 0;               // octet 0 (droite) pour afficheur 7 segments                    
//
//const int nitermax = 10000;         // Nbre d'it�ration max de la boucle de lecture d'acquisition (limite pour tests)
//									 // changer la condition de boucle sans cette limite selon le besoin de l'application
//const int delai_boucle = 10;         // delai d'attente ajout� dans la boucle de lecture en ms
//
//// numeros de registres correspondants pour les echanges FPGA <-> PC  ...
//unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
//unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
//unsigned const int nreg_lect_cmpt_t = 2;    // fpga -> PC  compteur temps FPGA -> PC 
//unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
//unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
//unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
//unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
//unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
//unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
//unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
//unsigned const int nreg_ecri_led = 10;

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
	void pause();

	//Menu Score
	void augmenterScore(int nbLigne);
	void augmenterLevel();
	//void loadHighscore();
	void checkerScore();

	//Menu hold
	void changerPiece();

	//Lecture FPGA
	//int lireFPGA();
	//Getter Pieces
	Piece getPieceHold();
	Piece getPieceSuivante();
protected:
	void paintEvent(QPaintEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent* event);


public slots:
	void moveDownPiece();
	//void unpauseGame();

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
	int compteur;
	int difficulte;
	std::vector<Player> historique;
	Player* player;

	// Qt
	QGridLayout* layout;
	QTimer* timer;
	bool isPaused;
	bool isStarted;
	QWidget *fenetre;

};
