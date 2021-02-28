#include "Board.h"

Board::Board() {
	resetBoard();
	score = 0;
	game_over = false;
	level = 0;
}

void Board::startGame() {
	int cpt = 0;
	
	while (game_over == false) { // Pour tester les pieces une apres l'autre
		if (loadPiece(cpt)) {
			print(ADD);
			moveDownPiece();
			cpt++;
			if (cpt == 7) cpt = 0;
		}
	}

	std::cout << "********* GAME OVER ******** \n";
}

bool Board::loadPiece(int num_piece) {
	piece.loadPiece(num_piece);

	for (int i = 0; i < 4; i++) { // verif si possible de placer pieces a pos initiale 
		if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne] == 1) {
			game_over = true; // jeu termine
			return false; // pas possible de loader la piece 
		}
	}
	return true;
}

void Board::movePiece() { // bouger gauche/droite
	
	switch (_getch()) { // manque des conditions pour les limites du board
	case KEY_DOWN:
		break;
	case KEY_UP:
		break;
	case KEY_RIGHT:
		piece.move(RIGHT);
		break;
	case KEY_LEFT:
		piece.move(LEFT);
		break;
	}
}

void Board::moveDownPiece() {
	bool possible = true;
	do {
		print(REMOVE);
		for (int i = 0; i < 4; i++) { // verifie si possible pour chaque carre de la piece
			if (cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne] == 1 ||
				piece.getCarre(i).ligne + 1 == LIGNES) {
				possible = false;
			}
		}
		
		if (possible) {
			piece.goDown();
			if(_kbhit()) movePiece(); // si une touche a ete pressee
		}
			
		print(ADD);
	} while (possible == true);
}

void Board::resetBoard() {
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			cases[i][j] = 0;
		}
	}
}

void Board::print(int state) {
	for (int i = 0; i < 4; i++) {
		cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne] = state;
	}
	system("CLS");
	printBoard();
	Sleep(250);
}

void Board::printBoard() {
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
