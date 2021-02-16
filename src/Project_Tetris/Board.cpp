#include "Board.h"

Board::Board() {
	resetBoard();
	score = 0;
	game_over = false;
	level = 0;	
}

void Board::startGame() {
	int cpt = 0;
	while(game_over == false) { // Pour tester les pièces une après l'autre
		loadPiece(cpt);
		printPiece(ADD);
		moveDownPiece();
		cpt++;
		if (cpt == 7) cpt = 0;
	}
	printPiece(REMOVE);
	std::cout << "********* GAME OVER ******** \n";
}

void Board::loadPiece(int num_piece) {
	piece.loadPiece(num_piece);

	for (int i = 0; i < 4; i++) { // vérif si pièces à pos initiale des pièces
		if (cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne] == 1) {
			game_over = true;
		}
	}
}

void Board::movePiece() { // bouger gauche/droite

	/*
	test flèches 

	int charac = 0;

	for(int i = 0; i < 3; i++) {
		charac = _getch();
		charac = _getch();

		switch (charac)
		{
		case KEY_DOWN:
			std::cout << "key down\n";
			break;
		case KEY_UP:
			std::cout << "key up\n";
			break;
		case KEY_RIGHT:
			std::cout << "key right\n";
			piece.move(RIGHT);
			break;
		case KEY_LEFT:
			std::cout << "key left\n";
			piece.move(LEFT);
			break;
		}
	}
	*/
}

void Board::moveDownPiece() { 
	bool possible = true;
	if (game_over == false) {
		do {
			printPiece(REMOVE);
			// verifier si possible
			for (int i = 0; i < 4; i++) { // vérif si possible pour chaque carré de la pièce
				if (cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne] == 1 ||
					cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne] == -1) {
					possible = false;
				}
			}

			if (possible)
				piece.goDown();
			printPiece(ADD);
		} while (possible == true);
	}
}

void Board::resetBoard() {
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			cases[i][j] = 0;
		}
	}

	for (int i = 0; i < COLONNES; i++) {
		cases[LIGNES][i] = -1;
	}
}

void Board::printPiece(int state) {
	for (int i = 0; i < 4; i++) {
		cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne] = state;
	}
	system("CLS");
	print();
	Sleep(250);
}

void Board::print() {
	for (int i = 0; i < LIGNES; i++) {
		std::cout << "| ";
		for (int j = 0; j < COLONNES; j++) {
			if (cases[i][j])
				std::cout << " x ";
			else
				std::cout << "   ";
		}
		std::cout << " |\n";
	}
}
