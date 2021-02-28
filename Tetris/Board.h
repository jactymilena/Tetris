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
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ADD 1
#define REMOVE 0

class Board {
public:
	Board();
	void startGame();
	void resetBoard();
	void print();
	void loadPiece(int num_piece);
	void printPiece(int state);
	void moveDownPiece();
	void movePiece();
	void restart();
	bool verifLigne();
	void enleverLigne();
	void tournerPiece();

	//Menu Score
	void menuScore();
	void augmenterScore();
	void prochainePiece();
	void augmenterLevel();


private:
	int cases[LIGNES + 1][COLONNES];
	bool game_over;
	int score;
	int level;
	Piece piece;
	Piece pieceApres;
};
