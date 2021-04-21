/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: Board.cpp
Date: 9 avril 2021
But: Contient les intéractions avec les pièces de l'aire de jeu
====================================*/

#include "Board.h"

bool statutport = false;            // statut du port de communication qui sera cree

int compteur_temps = 0;
int swt = 0;                         // donnee recue du FPGA
int aff7sg_octet0 = 0;               // octet 0 (droite) pour afficheur 7 segments
int aff7sg_octet1 = 0;               // octet 0 (droite) pour afficheur 7 segments                    

const int nitermax = 10000;         // Nbre d'itération max de la boucle de lecture d'acquisition (limite pour tests)
									 // changer la condition de boucle sans cette limite selon le besoin de l'application
const int delai_boucle = 10;         // delai d'attente ajouté dans la boucle de lecture en ms

// numeros de registres correspondants pour les echanges FPGA <-> PC  ...
unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
unsigned const int nreg_lect_cmpt_t = 2;    // fpga -> PC  compteur temps FPGA -> PC 
unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
unsigned const int nreg_ecri_led = 10;


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

	modeFPGA = false;

	// Timer
	timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(moveDownPiece()));
	QObject::connect(this, SIGNAL(declencherHold()), fenetreJeu, SLOT(slotPourTrigeredHold()));
	QObject::connect(this, SIGNAL(declencherSuivante()), fenetreJeu, SLOT(slotPourTrigeredSuivante()));
	isPaused = false;
	isStarted = false;

	// Carte FPGA
	timerFPGA = new QTimer(this);
	QObject::connect(timerFPGA, SIGNAL(timeout()), this, SLOT(lireFPGA()));
}

void Board::setModeFPGA(bool mode) {
	this->modeFPGA = mode;
}

bool Board::getModeFPGA() {
	return this->modeFPGA;
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
	resetBoard();
	startGame();
}

//Attrape les évènements du clavier et effectue les commandes propres
void Board::keyPressEvent(QKeyEvent* event) {
	bool canGoDown = true;
	if (!isPaused) {

		if ((event->key() == Qt::Key_Right)) {
			pieceState(REMOVE);

			if (verifMove(RIGHT)) {
				piece.move(RIGHT);
				mciSendString(L"close bubble", NULL, 0, NULL);
				mciSendString(L"open bubble-pop.mp3 type mpegvideo alias bubble", nullptr, 0, nullptr);
				mciSendString(L"play bubble", NULL, 0, NULL);
			}
			pieceState(ADD);

		}
		else if ((event->key() == Qt::Key_Left)) {
			pieceState(REMOVE);

			if (verifMove(LEFT)) {
				piece.move(LEFT);
				mciSendString(L"close bubble", NULL, 0, NULL);
				mciSendString(L"open bubble-pop.mp3 type mpegvideo alias bubble", nullptr, 0, nullptr);
				mciSendString(L"play bubble", NULL, 0, NULL);
			}
			pieceState(ADD);

		}
		else if ((event->key() == Qt::Key_Down)) {
			pieceState(REMOVE);
			if (verifMove(DOWN)) {
				piece.goDown();
			}
			pieceState(ADD);

		}
		else if ((event->key() == Qt::Key_W)) {

			if (nouvellePiece) {
				pieceState(REMOVE);
				nouvellePiece = false;
				changerPiece();
			}
			

			emit declencherHold();
		}
		else if (event->key() == Qt::Key_Q) {
			pieceState(REMOVE);
			movePiece(TURN_LEFT);
			pieceState(ADD);

		}
		else if (event->key() == Qt::Key_E) {
			pieceState(REMOVE);
			movePiece(TURN_RIGHT);
			pieceState(ADD);

		}

	}

	if (event->key() == Qt::Key_Escape) {
		if (!isPaused) { // en pause
			pause(true);
		}
		else { // retour au jeu
			isPaused = false;
			timer->start(difficulte);
			timerFPGA->start(10);
			mciSendString(L"resume maintheme", NULL, 0, NULL);
		}

	}
	update();

}


//Met en pause le jeu et la musique
void Board::pause(bool cond) {
	if (cond) {
		mciSendString(L"pause maintheme", NULL, 0, NULL);
	}
	isPaused = true;
	timer->stop();
	timerFPGA->stop();
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
	timerFPGA->start(50);
	isStarted = true;
	srand((int)time(0));
	pieceApres.loadPiece(rand() % 7);
	loadPiece(pieceApres.getNumPiece());
}

// Mouvement des pieces
void Board::movePiece(int direction) {
	switch (direction) {
	case (RIGHT):
		if (verifMove(RIGHT)) {
			piece.move(RIGHT);
		}
		break;
	case (LEFT):
		if (verifMove(LEFT)) {
			piece.move(LEFT);
		}
		break;
	case (TURN_RIGHT):
		if (piece.getNumPiece() != O) {
			piece.turn(RIGHT);
			if (!verifMove(TURN_RIGHT)) {
				piece.unturned();
			}
		}
		break;
	case (TURN_LEFT):
		if (piece.getNumPiece() != O) {
			piece.turn(LEFT);

			if (!verifMove(TURN_LEFT)) {
				piece.unturned();
			}
		}
		break;
	}
	pieceState(ADD);
	update();
}

// Communication avec la carte FPGA 
void Board::lireFPGA() {
	qDebug() << "Mode FPGA " << modeFPGA;
	CommunicationFPGA port;
	static int canal_a_afficher = 0;
	int indice_canal_a_afficher = 0;
	int stat_btn = 0;
	int statut_circuit = 0;
	if (modeFPGA) {
		statutport = port.lireRegistre(nreg_lect_stat_btn, statut_circuit);

		if (statutport) statutport = port.lireRegistre(nreg_lect_stat_btn, stat_btn);     // lecture statut et BTN
		else { qDebug() << "Erreur du port nreg_lect_stat_btn"; exit(1); }

		int echconv[4];
		if (statutport) statutport = port.lireRegistre(nreg_lect_can0, echconv[0]);       // lecture canal 0
		else { qDebug() << "Erreur du port nreg_lect_can0"; exit(1); }
		if (statutport) statutport = port.lireRegistre(nreg_lect_can1, echconv[1]);       // lecture canal 1
		else { qDebug() << "Erreur du port nreg_lect_can1"; exit(1); }
		if (statutport) statutport = port.lireRegistre(nreg_lect_can2, echconv[2]);       // lecture canal 2
		else { qDebug() << "Erreur du port nreg_lect_can2"; exit(1); }
		if (statutport) statutport = port.lireRegistre(nreg_lect_can3, echconv[3]);       // lecture canal 3
		else { qDebug() << "Erreur du port nreg_lect_can3"; exit(1); }
		if (!statutport) {
			qDebug() << "Erreur du port dans la boucle";
			exit(1);
		}
		statutport = port.ecrireRegistre(nreg_ecri_led, 1);
		//if ((stat_btn & 1) != 0)
		
			
			qDebug() << echconv[0];
			qDebug() << echconv[2];

			//Phonème A
			if ((echconv[0] > 50)&& (echconv[1] < 180) && (echconv[3]  < 180) && (echconv[2] < 180))
			{
				moinsViteA++;
				moinsViteI = 0;
				moinsViteU = 0;
				if(moinsViteA % 5 == 0)
				{
					pieceState(REMOVE);
					if (verifMove(RIGHT)) {
					
						piece.move(RIGHT);
					}
					pieceState(ADD);
				}

			}
			//Phonème I
			else if ((echconv[0] < 80) && (echconv[1] < 20) && (echconv[2] < 90) && (echconv[3] > 180))
			{
				moinsViteA = 0;
				moinsViteI++;
				moinsViteU = 0;
				if (moinsViteI % 5 == 0)
				{
					pieceState(REMOVE);
					if (verifMove(LEFT)) {
						piece.move(LEFT);
					}
					pieceState(ADD);
				}

			}
			//Phonème U
			else if ((echconv[0] < 80) && (echconv[1] < 20) && (echconv[2] < 90) && (echconv[3] > 180))
			{
				moinsViteA = 0;
				moinsViteI = 0;
				moinsViteU ++;
				if (moinsViteU % 5 == 0)
				{
					pieceState(REMOVE);
					if (piece.getNumPiece() != O) {
						piece.turn(RIGHT);
						if (!verifMove(TURN_RIGHT)) {
							piece.unturned();
						}
					}
					pieceState(ADD);
				}

			}
			else
			{
				moinsViteA = 0;
				moinsViteI = 0;
				moinsViteU = 0;
			}
			//Phonème I
			/*else if ((echconv[0] > 90) && (echconv[2] > 180) && (echconv[1] > 50))
			{
				pieceState(REMOVE);
				if (piece.getNumPiece() != O) {
					piece.turn(LEFT);

					if (!verifMove(TURN_LEFT)) {
						piece.unturned();
					}
				}
				pieceState(ADD);

			}*/
		
		if ((stat_btn & 2) != 0)
		{
			canal_a_afficher++;

			if (canal_a_afficher > 3) canal_a_afficher = 0;
		}
		qDebug() << "A:" << moinsViteA;
		qDebug() << "I:" << moinsViteI;
		qDebug() << "U:" << moinsViteU;
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, canal_a_afficher);                    // envoyer numero canal_a_afficher afficheur 7 segments
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, echconv[canal_a_afficher]); // envoyer valeur echconv[] afficheur 7 segments
	}


}


//Met une pièce dans le board
bool Board::loadPiece(int num_piece) {
	piece.loadPiece(num_piece);
	
	for (int i = 0; i < 4; i++) { // verif si possible de placer pieces a pos initiale 
		if (cases[piece.getCarre(i).ligne][piece.getCarre(i).colonne].value == 1) {
			game_over = true; // jeu termine
			timer->stop();
			timerFPGA->stop();
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
	pieceState(REMOVE);
	for (int i = 0; i < LIGNES; i++) {
		for (int j = 0; j < COLONNES; j++) {
			cases[i][j].value = 0;
			cases[i][j].color = Qt::white;
		}
	}
	mciSendString(L"resume maintheme", NULL, 0, NULL);
	mciSendString(L"set maintheme speed 1000", nullptr, 0, 0);
	pieceHold.setNumPiece(7);
	emit declencherHold();
	game_over = false;
	isPaused = false;
	isStarted = false;
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