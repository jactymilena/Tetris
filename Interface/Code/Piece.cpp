/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: Piece.cpp
Date:           1 avril 2021
But:            Contient les données de la pièce
====================================*/

#include "Piece.h"

Piece::Piece() {
	numPiece = 7;
	numColor = 0;
}

Carre::Carre() {
	ligne = 0;
	colonne = 0;
}

//Fonction pour charger une piece selon le numéro de pièce rentré en paramètre.
void Piece::loadPiece(int num_piece) {
	// 7 types de pi�ces
	if (num_piece >= 0 && numPiece <= 7)
	{
		numPiece = num_piece;
	}

	switch (num_piece) { // position initial des carr�s de la pi�ce 
	case I:
		numColor = 0;
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
		numColor = 1;
		carres[0].ligne = 1;
		carres[0].colonne = 3;

		carres[1].ligne = 0;
		carres[1].colonne = 4;

		carres[2].ligne = 0;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case J:
		numColor = 2;
		carres[0].ligne = 0;
		carres[0].colonne = 2;

		//pivot
		carres[1].ligne = 1;
		carres[1].colonne = 2;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case Z:
		numColor = 3;
		carres[0].ligne = 0;
		carres[0].colonne = 2;

		//pivot
		carres[1].ligne = 0;
		carres[1].colonne = 3;

		carres[2].ligne = 1;
		carres[2].colonne = 3;

		carres[3].ligne = 1;
		carres[3].colonne = 4;

		break;
	case T:
		numColor = 4;
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
		numColor = 5;
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
		numColor = 6;
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
		numColor = 0;
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


// Fontion qui fait descendre la pièce.
void Piece::goDown() {
	for (int i = 0; i < 4; i++) {
		carres[i].ligne += 1;
	}
}

// Fonction qui fait bouger la pièce selon la direction rentrée en paramètre
void Piece::move(int direction) { // gauche -1, droite 1
	for (int i = 0; i < 4; i++) {
		carres[i].colonne += direction;
	}
}

// Getter : retourne le numréro de la couleur 
int Piece::getNumColor() const {
	return numColor;
}

// Getter : retourne un carré de la pièce selon l'index rentré en paramètre
Carre Piece::getCarre(int index) const {
	return carres[index];
}

// Fontion qui retourne un carré de la pièce gardée en mémoire selon l'index rentré en paramètre
Carre Piece::getMemoire(int index) const {
	return memoireVecteur[index];
}

// Fonction qui remet les coordonnées de la pièce égales à celle gardée en mémoire pour défaire l'action tourner
void Piece::unturned() {
	for (int i = 0; i < 4; i++) {
		carres[i].ligne = memoireVecteur[i].ligne;
		carres[i].colonne = memoireVecteur[i].colonne;
	}
}

// Fonction qui fait tourner la pièce selon la direction rentrée en paramètre
void Piece::turn(int direction) { 

	for (int i = 0; i < 4; i++) {
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
		else if (direction == RIGHT) {//Tourner a droite
			//Recherche du Vecteur transposé
			vecteurTranspose[i].ligne = (0 * vecteurRelatif[i].ligne) + (1 * vecteurRelatif[i].colonne);
			vecteurTranspose[i].colonne = (-1 * vecteurRelatif[i].ligne) + (0 * vecteurRelatif[i].colonne);
		}

		carres[i].ligne = carres[INDEX_PIVOT].ligne + vecteurTranspose[i].ligne;
		carres[i].colonne = carres[INDEX_PIVOT].colonne + vecteurTranspose[i].colonne;
	}
}

// Getter : retourne le numréro de la pièce
int Piece::getNumPiece() const
{
	return numPiece;
}

// Setter : change la valeur du numéro de la pièce selon le numéro rentré en paramètre
void Piece::setNumPiece(int numPiece)
{
	this->numPiece = numPiece;
}
