#pragma once
#include <iostream>
//#include "Carre.h"

#define LEFT -1
#define RIGHT 1


struct Carre {
	int ligne;
	int colonne;
	Carre();
};

class Piece {
public:
	Piece();
	void goDown();
	void move(int direction);
	void turn();
	void loadPiece(int num_piece);
	void print();

	Carre getCarre(int index) const;
	int getNumPiece()const;
	void setNumPiece(int numPiece);

	
private:
	Carre carres[4];
	int numPiece;
};
