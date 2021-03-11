#pragma once
#include <iostream>
//#include "Carre.h"

#define LEFT -1
#define RIGHT 1
//Nom des Tetrominos
#define I 0 
#define O 1 
#define J 2 
#define Z 3 
#define T 4 
#define L 5
#define S 6


struct Carre {
	int ligne;
	int colonne;
};

class Piece {
public:
	Piece();
	void goDown();
	void move(int direction);
	void turn(int direction);//Simon
	void loadPiece(int num_piece);
	void print();

	Carre getCarre(int index) const;

private:
	Carre carres[4];
	int pivot[2];//Permet de faire tourner la píece autour d'une case
};
