/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: Board.cpp
Date: 9 avril 2021
But: Contient les intéractions avec les pièces de l'aire de jeu
====================================*/

#include "Board.h"

Case::Case() {
	value = 0;
}

Board::Board(QWidget* fenetreJeu, Player* playerPrincipal) : QFrame(), player(playerPrincipal) {
	fenetre = fenetreJeu;
	// set Frame
	setFrameStyle(QFrame::Box | QFrame::Plain);
	setLineWidth(3);
	setMidLineWidth(3);
	setStyleSheet("background : transparent; border: 2px solid white"); 
	activateWindow();
	setMinimumHeight(550);
	setMinimumWidth(200);
	// Board init
	resetBoard();
	
	// Timer
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveDownPiece()));
	QObject::connect(this, SIGNAL(declencherHold()), fenetreJeu, SLOT(slotPourTrigeredHold()));
	QObject::connect(this, SIGNAL(declencherSuivante()), fenetreJeu, SLOT(slotPourTrigeredSuivante()));
	isPaused = false;
	isStarted = false;
}

//Attrape l'évènement de la souris qui clique sur le board
void Board::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		if (isStarted == false) {
			isStarted = true;
			startGame();
			update();
		}
		if (game_over == true) {
			game_over = false;
			resetBoard();
			startGame();
		}
	}
}

//Remet le board dans son état de base
void Board::restart() {
	if (game_over == true) {
		game_over = false;
		resetBoard();
		startGame();
	}
}

//Attrape les évènements du clavier et effectue les commandes propres
void Board::keyPressEvent(QKeyEvent* event) {
	bool canGoDown = true;
	pieceState(REMOVE);
	if (!isPaused) {
		if ((event->key() == Qt::Key_Right) && verifMove(RIGHT)) {
			piece.move(RIGHT);
		}
		else if ((event->key() == Qt::Key_Left) && verifMove(LEFT)) {
			piece.move(LEFT);
		}
		else if ((event->key() == Qt::Key_Down)) {
			canGoDown = verifMove(DOWN);
			if (canGoDown) {
				moveDownPiece();
			}
			/*else {
				pieceState(ADD);
				verifLigne();
				loadPiece(pieceApres.getNumPiece());
				nouvellePiece = true;
			}*/
		}
		else if ((event->key() == Qt::Key_W) &&	nouvellePiece) {
			nouvellePiece = false;
			changerPiece();
			pieceState(ADD);
			emit declencherHold();
		}
		else if (event->key() == Qt::Key_Q) {
			if (piece.getNumPiece() != O) {
				piece.turn(LEFT);

				if (!verifMove(TURN_LEFT)) {
					piece.unturned();
				}
			}
		}
		else if (event->key() == Qt::Key_E) {
			if (piece.getNumPiece() != O) { 
				piece.turn(RIGHT);
				if (!verifMove(TURN_RIGHT)) {
					piece.unturned();
				}
			}
		}
	}

	if (event->key() == Qt::Key_Escape) {
		if (!isPaused) { // en pause
			pause();
		}
		else { // retour au jeu
			isPaused = false;
			timer->start(difficulte);
			mciSendString(L"resume maintheme", NULL, 0, NULL);
			update();
		}
	}

	pieceState(ADD);

	update();
}

//Met en pause le jeu et la musique
void Board::pause() {
	isPaused = true;
	mciSendString(L"pause maintheme", NULL, 0, NULL);
	timer->stop();
	update();
}

//Override la fonction du QFrame pour repeindre le tableau
void Board::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setPen(QPen(Qt::white));
	QRect rect = contentsRect();
	float largeurCarre = contentsRect().width() / (float)COLONNES;
	float hauteurCarre = contentsRect().height() / (float)LIGNES;
	
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			if (cases[i][j].value == 1) {
				painter.setBrush(QBrush(cases[i][j].color));
				painter.drawRect(QRect(j * largeurCarre + rect.topLeft().x(), i * hauteurCarre + rect.topLeft().y(), largeurCarre, hauteurCarre));

			}
			else {
				//QBrush(QColor(170, 170, 170, 180)
				painter.setBrush(QColor(170, 170, 170, 0));
				painter.drawRect(QRect(j * largeurCarre + rect.topLeft().x(), i * hauteurCarre + rect.topLeft().y(), largeurCarre, hauteurCarre));
			}
		}
	}

	if (isPaused || isStarted == false || game_over) {
		painter.fillRect(rect, QBrush(QColor(170, 170, 170, 180)));
		painter.setPen(Qt::white);
		QFont font("Arial", 20);
		font.setWeight(QFont::Bold);
		painter.setFont(font);

		if (!isStarted) {
			painter.drawText(rect, Qt::AlignCenter, "Click to start");
		}
		if (isPaused) {
			painter.drawText(rect, Qt::AlignCenter, "ESC to restart");
		}
		if (game_over) {
			painter.drawText(rect, Qt::AlignCenter, "GAME OVER");
		}
	}
	
}

//Commence le jeu
void Board::startGame() {
	timer->start(difficulte);
	isStarted = true;
	srand((int)time(0));
	pieceApres.loadPiece(rand() % 7);
	loadPiece(pieceApres.getNumPiece());
}

//Met une pièce dans le board
bool Board::loadPiece(int num_piece) {
	piece.loadPiece(num_piece);
	

	for (int i = 0; i < 4; i++) { // verif si possible de placer pieces a pos initiale 
		if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne].value == 1) {
			game_over = true; // jeu termine
			timer->stop();
			emit gameOverSignal();
			return false; // pas possible de loader la piece 
		}
	}
	pieceApres.loadPiece(rand() % 7);
	emit declencherSuivante();
	return true;
}

//Vérifie si la pièce peut bouger
bool Board::verifMove(int direction) {

	switch (direction) {
	case RIGHT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne + 1].value == 1 ||
				piece.getCarre(i).colonne + 1 == COLONNES) {
				return false;
			}
		}
		break;
	case LEFT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne - 1].value == 1 ||
				piece.getCarre(i).colonne - 1 < 0) {
				return false;
			}
		}
		break;

	case DOWN:
		for (int i = 0; i < 4; i++) {
			if (piece.getCarre(i).ligne + 1 != LIGNES) {
				if (cases[piece.getCarre(i).ligne + 1][piece.getCarre(i).colonne].value == 1) { // la piece ne peut plus descendre 
					return false;
				}
			}
			else {
				return false;
			}
		}
		break;

	case TURN_RIGHT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne].value == 1 ||
				piece.getCarre(i).colonne >= COLONNES ||
				piece.getCarre(i).colonne <= 0 || piece.getCarre(i).ligne > LIGNES) {
				return false;
			}
		}
		break;

	case TURN_LEFT:
		for (int i = 0; i < 4; i++) {
			if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne].value == 1 ||
				piece.getCarre(i).colonne >= COLONNES ||
				piece.getCarre(i).colonne <= 0 || piece.getCarre(i).ligne > LIGNES) {
				return false;
			}
		}
		break;
	}
	return true;
}

//Bouge la pièce d'une case vers le bas
void Board::moveDownPiece() {
	pieceState(REMOVE);
	if (verifMove(DOWN)) {
		piece.goDown();
		pieceState(ADD);
	}
	else {
		pieceState(ADD);
		verifLigne();
		loadPiece(pieceApres.getNumPiece());
		nouvellePiece = true;
	}
	update();
}

bool Board::getIsStarted() {
	return isStarted;
}

//Repeint les valeurs de base du board
void Board::resetBoard() {
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			cases[i][j].value = 0;
			cases[i][j].color = Qt::white;
		}
	}
	mciSendString(L"set maintheme speed 1000", nullptr, 0, 0);
	pieceHold.setNumPiece(7);
	emit declencherHold();
	game_over = false;
	player->setLevel(0);
	player->setScore(0);
	difficulte = 500;
	nouvellePiece = true;
}


void Board::pieceState(int state) {
	QColor color = Qt::white;

	if (state == ADD) {
		color = colorTab[piece.getNumColor()];
	}

	for (int i = 0; i < 4; i++) {
		cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne].value = state;
		cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne].color = color;
	}
}

//Augmente le score 
void Board::augmenterScore(int nbLigne) {
	if (nbLigne == 1) {
		player->setScore(player->getScore() + 50 * nbLigne);
	}
	else if (nbLigne == 2) {
		player->setScore(player->getScore() + 150);
	}
	else if (nbLigne == 3) {
		player->setScore(player->getScore() + 300);
	}
	else if (nbLigne == 4) {
		player->setScore(player->getScore() + 500);
	}
	
	augmenterLevel();
}

//Regarde s'il faut augmenter le niveau
void Board::augmenterLevel() {
	int speed = 0;
	if (player->getScore() != 0)
	{
		if (player->getScore() % SCORE == 0)
		{
			difficulte -= 20;
			player->setLevel(player->getLevel() + 1);
			speed = player->getLevel() * 20 + 1000;
			std::string string1 = "set maintheme speed " + std::to_string(speed);
			std::wstring wstring1 = std::wstring(string1.begin(), string1.end());
			const wchar_t* wchar1 = wstring1.c_str();
			
			mciSendString(wchar1, nullptr, 0, 0);
			if (difficulte < 100)
			{
				difficulte = 100;
				//player->setLevel(player->getLevel() + 1);

			}

			timer->stop();
			timer->start(difficulte);
		}
	}
}

//Vérifier toutes les cases d'une pièce
bool Board::verifLigne() {
	int minLigne = piece.getCarre(0).ligne;
	int maxLigne = piece.getCarre(0).ligne;
	int compteurX = 0;
	int compteurLigne = 0;
	for (int i = 1; i < 4; i++) { // V�rifier les quatres carrees pour avoir la ligne minimale et maximale
		if (piece.getCarre(i).ligne < minLigne)
		{
			minLigne = piece.getCarre(i).ligne;
		}
		if (piece.getCarre(i).ligne > maxLigne)
		{
			maxLigne = piece.getCarre(i).ligne;
		}
	}
	
	for (int z = minLigne; z <= maxLigne; z++)
	{

		compteurX = 0;
		for (int j = 0; j < COLONNES; j++)
		{
			if (cases[z][j].value == 1) {
				compteurX++;
			}
		}
		if (compteurX == COLONNES)
		{
			enleverLigne(z);
			compteurLigne++;
		}
	}
	if (compteurLigne > 0)
	{
		augmenterScore(compteurLigne);
	}

	return true;
}

//Enlève les lignes
void Board::enleverLigne(int i)
{
	for (int w = i; w > 0; w--) 
	{
		for (int j = 0; j < COLONNES; j++)
		{
			cases[w][j] = cases[w - 1][j];
		}
	}
	update();
}

//Gère les pièces lorsqu'il y a un hold
void Board::changerPiece()
{
	if (pieceHold.getNumPiece() == 7)
	{
		pieceHold.loadPiece(piece.getNumPiece());
		piece.loadPiece(pieceApres.getNumPiece());
		loadPiece(piece.getNumPiece());
	}
	else
	{
		int numHold = pieceHold.getNumPiece();
		pieceHold.loadPiece(piece.getNumPiece());
		piece.loadPiece(numHold);
	}
}

//Getters
Piece Board::getPieceHold()
{
	return pieceHold;
}
Piece Board::getPieceSuivante()
{
	return pieceApres;
}