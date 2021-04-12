#pragma once
#include <iostream>
#include <QRgb>
#include <QColor>
#include <QDebug>
#include <QRandomGenerator>

#define LEFT -1
#define RIGHT 1
#define TURN_RIGHT 2
#define TURN_LEFT 3

//Nom des Tetrominos
#define I 0 
#define O 1 
#define J 2 
#define Z 3 
#define T 4 
#define L 5
#define S 6
#define INDEX_PIVOT 1


const QRgb colorTab[5] = { 
	0x0341AE, 0x72CB3B, 0xFFD500, 0xFF971C, 0xFF3213 //blue, green, yellow, orange, red
};

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
	void turn(int direction);
	void unturned();
	void loadPiece(int num_piece, int color_num);
	void print();

	Carre getCarre(int index) const;
	int getNumColor() const;
	int getNumPiece() const;
	void setNumPiece(int numPiece);
	Carre getMemoire(int index) const;

private:
	Carre carres[4];
	Carre vecteurRelatif[4];
	Carre vecteurTranspose[4];
	Carre memoireVecteur[4];
	int numPiece;
	int numColor;
};
