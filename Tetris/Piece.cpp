#include "Piece.h"


Piece::Piece() {
	numPiece = 0;
}

Carre::Carre() {
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
	case I:
		carres[0].ligne = 0;
		carres[0].colonne = 4;

		//pivot
		carres[1].ligne = 0;
		carres[1].colonne = 3;

		carres[2].ligne = 0;
		carres[2].colonne = 2;

		carres[3].ligne = 0;
		carres[3].colonne = 5;

		break;
	case O:
		carres[0].ligne = 1;
		carres[0].colonne = 3;

		carres[1].ligne = 0;
		carres[1].colonne = 4;
		
		carres[2].ligne = 0;//
		carres[2].colonne = 3;//

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case J:
		carres[0].ligne = 0;//
		carres[0].colonne = 2; //

		//pivot
		carres[1].ligne = 1;
		carres[1].colonne = 2;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case Z:
		carres[0].ligne = 0;
		carres[0].colonne = 2;

		//pivot
		carres[1].ligne = 0;
		carres[1].colonne = 3;

		carres[2].ligne = 1;//
		carres[2].colonne = 3;//

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case T:
		carres[0].ligne = 0;
		carres[0].colonne = 3;

		//pivot
		carres[1].ligne = 1;
		carres[1].colonne = 3;
                       
		carres[2].ligne = 1;
		carres[2].colonne = 2;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case L:
		carres[0].ligne = 0;
		carres[0].colonne = 4;

		carres[1].ligne = 1;
		carres[1].colonne = 3;

		carres[2].ligne = 1;
		carres[2].colonne = 2;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case S:
		carres[0].ligne = 0;
		carres[0].colonne = 3;

		carres[1].ligne = 1;
		carres[1].colonne = 3;

		carres[2].ligne = 1;
		carres[2].colonne = 2;

		carres[3].ligne = 0;
		carres[3].colonne = 4;

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

Carre Piece::getMemoire(int index) const {
	return memoireVecteur[index];
}

void Piece::unturned() {
	for (int i = 0; i < 4; i++) {
		carres[i].ligne = memoireVecteur[i].ligne;
		carres[i].colonne = memoireVecteur[i].colonne;
	}

}

void Piece::print() {
	for (int i = 0; i < 4; i++) {
		std::cout << "( " << carres[i].ligne << ", " << carres[i].colonne << " )\n";
	}
}

void Piece::turn(int direction) { //https://www.youtube.com/watch?v=Atlr5vvdchY&ab_channel=GoranMilovanovic essentiel pour faire la rotation

	for(int i = 0; i < 4; i++){
		//Enregistre la premiere position
		memoireVecteur[i].ligne = carres[i].ligne;
		memoireVecteur[i].colonne = carres[i].colonne;
		//Recherche du vecteur relatif
		vecteurRelatif[i].ligne = carres[i].ligne - carres[INDEX_PIVOT].ligne;
		vecteurRelatif[i].colonne = carres[i].colonne - carres[INDEX_PIVOT].colonne;


		//Recherche du Vecteur transposé
		//Matrice de rotation de 2/pi c'est   0 -1
		//                                    1  0
		if (direction == LEFT) {//Tourner a gauche
			vecteurTranspose[i].ligne = (0 * vecteurRelatif[i].ligne) + (-1 * vecteurRelatif[i].colonne);
			vecteurTranspose[i].colonne = (1 * vecteurRelatif[i].ligne) + (0 * vecteurRelatif[i].colonne);
		}

		//Matrice de rotation de 2/pi c'est   0  1
		//                                   -1  0
		else if(direction == RIGHT){//Tourner a droite
			//Recherche du Vecteur transposé
			vecteurTranspose[i].ligne = (0 * vecteurRelatif[i].ligne) + (1 * vecteurRelatif[i].colonne);
			vecteurTranspose[i].colonne = (-1 * vecteurRelatif[i].ligne) + (0 * vecteurRelatif[i].colonne);
		}

		carres[i].ligne = carres[INDEX_PIVOT].ligne + vecteurTranspose[i].ligne;
		carres[i].colonne = carres[INDEX_PIVOT].colonne + vecteurTranspose[i].colonne;

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
