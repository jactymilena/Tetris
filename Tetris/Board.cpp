#include "Board.h"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

Board::Board() {
	resetBoard();
	score = 0;
	game_over = false;
	level = 0;
	difficulte = 1;
	compteur = 0;
}

void Board::startGame() {
	int cpt = 0;

	while (game_over == false) { // Pour tester les pieces une apres l'autre
		if (loadPiece(cpt)) {
			print();
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

void Board::movePiece() { // bouger gauche, droite, bas, tourner
	//std::cout << "Helloooo\n";
	if (GetAsyncKeyState(KEY_RIGHT) && verifMove(RIGHT))
	{
		piece.move(RIGHT);
	}

	if (GetAsyncKeyState(KEY_LEFT) && verifMove(LEFT))
	{
		piece.move(LEFT);
	}
	if (GetAsyncKeyState(KEY_DOWN) && verifMove(DOWN))
	{
		piece.goDown();
	}
	if (GetAsyncKeyState(KEY_Q))
	{
		std::cout << "Allo\n";
		piece.turn(LEFT);
	}

	//if (GetAsyncKeyState(KEY_E))
	//{
	//	piece.turn(RIGHT);
	//}

}

bool Board::verifMove(int direction) {
	switch (direction) {
	case RIGHT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne + 1] == 1 ||
				piece.getCarre(i).colonne + 1 == COLONNES) {
				return false;
			}
		}
		break;
	case LEFT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne - 1] == 1 ||
				piece.getCarre(i).colonne - 1 < 0) {
				return false;
			}
		}
		break;

	case DOWN:
		for (int i = 0; i < 4; i++) {
			if (piece.getCarre(i).ligne + 1 != LIGNES) {
				if (cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne] == 1) { // la piece ne peut plus descendre 
					return false;
				}
			}
			else { // la piece est rendu a la derniere ligne 
				return false;
			}
		}
		break;
/*
	case TURN_RIGHT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne + 1] == 1 ||
				piece.getCarre(i).colonne + 1 == COLONNES) {
				return false;
			}
		}
		break;
	case TURN_LEFT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne - 1] == 1 ||
				piece.getCarre(i).colonne - 1 < 0) {
				return false;
			}
		}
		break;
		*/
	}
	return true;
}

void Board::moveDownPiece() {
	bool possibleBas = true;
	bool possibleDroite = true;
	bool possibleGauche = true;

	do {
		pieceState(REMOVE);

		if (_kbhit()) movePiece();

		if ((possibleBas = verifMove(DOWN)) && (compteur == difficulte)) {
			piece.goDown();
			// si une touche a ete pressee
			compteur = 0;
		}

		print();
	} while (possibleBas == true);
	compteur = 0;
}

void Board::resetBoard() {
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			cases[i][j] = 0;
		}
	}
}

void Board::pieceState(int state) {
	for (int i = 0; i < 4; i++) {
		cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne] = state;
	}
}

/*
author: Ryan Pickelsimer
source: https://github.com/rpickelsimer/Tetris/blob/master/Tetris.cpp
Date: 2021-03-02
Description: Utilisation de sa fonction clear() servant à effacer l'écran.
			 Cela offre une alternative à la fonction system("cls") montrant
			 certaines lacunes au niveau de l'efficacité tant qu'au fait d'effacer
			 plusieurs lignes.
*/
void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

void Board::print() {
	pieceState(ADD);
	clear();//system("CLS");
	printBoard();
	std::this_thread::sleep_for(50ms);
	compteur++;
}

void Board::printBoard() {
	for (int i = 0; i < LIGNES; i++) {
		std::cout << "|";
		for (int j = 0; j < COLONNES; j++) {
			if (cases[i][j])
				std::cout << " x ";
			else
				std::cout << "   ";
		}
		std::cout << "|\n";
	}
}
