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
	void printBoard();
	bool loadPiece(int num_piece);
	void print();
	void moveDownPiece();
	void movePiece();
	void pieceState(int state);
	bool verifLigne(); // Aris
	void enleverLigne(); // Aris VVVVV
	void tournerPiece(); // Simon
	void prochainePiece(); // Simon

	//Menu Score
	void menuScore(); // Aris
	void augmenterScore(); // Aris
	void augmenterLevel(); // Aris


private:
	int cases[LIGNES][COLONNES];
	bool game_over;
	int score;
	int level;
	Piece piece;
	Piece pieceApres;
};
//asdfaasdfasd