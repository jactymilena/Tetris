#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "Piece.h"

#define LIGNES 18
#define COLONNES 8
#define KEY_UP 72
#define SPACE_BAR 32
#define KEY_DOWN 40
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define ADD 1
#define REMOVE 0
#define DOWN 0
#define SCORE 100
#define wKey 87

class Board {
public:
	Board();
	void startGame();
	void resetBoard();
	void printBoard();
	bool loadPiece(int num_piece);
	void print();
	void moveDownPiece();
	void movePiece(bool &nouvellePiece);
	void pieceState(int state);
	bool verifMove(int direction);
	bool verifLigne(); // Aris
	void enleverLigne(int i); // Aris 
	void tournerPiece(); // Simon
	void prochainePiece(); // Simon

	//Menu Score
	void menuScore(); // Aris
	void augmenterScore(int nbLigne); // Aris
	void augmenterLevel(); // Aris

	//Menu hold
	void changerPiece();
	void menuHold();

	//Menu Suivante
	void menuPieceSuivante();

private:
	int cases[LIGNES][COLONNES];
	bool game_over;
	int score;
	int level;
	Piece pieceHold;
	Piece piece;
	Piece pieceApres;
	int compteur;
	int difficulte;
	int min = 0;
	int max = 0;
};
