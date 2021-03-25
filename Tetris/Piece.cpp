#include "Piece.h"


Piece::Piece() {
}
Carre::Carre()
{
	ligne = 0;
	colonne = 0;
}
void Piece::loadPiece(int num_piece) {
	// id�e : avoir un fichier pour chaque piece avec la position de depart (matrice) 
	//        ou seulement les mettre dans fonction sans fichier
	// 7 types de pi�ces
	if (num_piece >= 0 && numPiece <= 7) 
	{
		numPiece = num_piece;
	}
	
	switch (num_piece) { // position initial des carr�s de la pi�ce  (code � rendre moins laid)
	case 0:
		carres[0].ligne = 0;
		carres[0].colonne = 2;

		carres[1].ligne = 0;
		carres[1].colonne = 3;

		carres[2].ligne = 0;
		carres[2].colonne = 4;

		carres[3].ligne = 0;
		carres[3].colonne = 5;

		break;
	case 1:
		carres[0].ligne = 0;
		carres[0].colonne = 3;

		carres[1].ligne = 0;
		carres[1].colonne = 4;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case 2:
		carres[0].ligne = 0;
		carres[0].colonne = 2;

		carres[1].ligne = 1;
		carres[1].colonne = 2;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case 3:
		carres[0].ligne = 0;
		carres[0].colonne = 2;

		carres[1].ligne = 0;
		carres[1].colonne = 3;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case 4:
		carres[0].ligne = 0;
		carres[0].colonne = 3;

		carres[1].ligne = 1;
		carres[1].colonne = 2;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case 5:
		carres[0].ligne = 0;
		carres[0].colonne = 4;

		carres[1].ligne = 1;
		carres[1].colonne = 2;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case 6:
		carres[0].ligne = 0;
		carres[0].colonne = 3;

		carres[1].ligne = 0;
		carres[1].colonne = 4;

		carres[2].ligne = 1;
		carres[2].colonne = 2;

		carres[3].ligne = 1;
		carres[3].colonne = 3;

		break;

	case 7:
		carres[0].ligne = -1;
		carres[0].colonne = -1;

		carres[1].ligne = -1;
		carres[1].colonne = -1;

		carres[2].ligne = -1;
		carres[2].colonne = -1;

		carres[3].ligne = -1;
		carres[3].colonne = -1;
		break;
	}
}

void Piece::goDown() {
	for (int i = 0; i < 4; i++) {
		carres[i].ligne += 1;
	}
}

void Piece::move(int direction) { // gauche -1, droite 1
	for (int i = 0; i < 4; i++) {
		carres[i].colonne += direction;
	}
}

Carre Piece::getCarre(int index) const {
	return carres[index];
}

void Piece::print() {
	for (int i = 0; i < 4; i++) {
		std::cout << "( " << carres[i].ligne << ", " << carres[i].colonne << " )\n";
	}
}

int Piece::getNumPiece() const
{
	return numPiece;
}

void Piece::setNumPiece(int numPiece)
{
	this->numPiece = numPiece;
}
