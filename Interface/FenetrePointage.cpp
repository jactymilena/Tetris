/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: FenetreDePointage.cpp
Date:           15 avril 2021
But:            Montre le pointage de l'utilisateur et sa position
====================================*/

#include "FenetrePointage.h"
#include "FenetrePrincipale.h"


FenetrePointage::FenetrePointage(Player* playerPrincipal) :
	QWidget(),
	layout(nullptr),
	usernameTitre(nullptr),
	positionTitreJoueur(nullptr),
	highscoreTitre(nullptr),
	scoreJoueur(nullptr),
	votreScore(nullptr),
	nomJoueur(nullptr),
	nomTitre(nullptr),
	scoreTitre(nullptr),
	positionJoueur(nullptr),
	positionTitre(nullptr),
	position(nullptr),
	name(nullptr),
	score(nullptr),
	highscore(nullptr),
	groupBoxScore(nullptr),
	groupBoxUser(nullptr),
	gridScore(nullptr),
	gridScoreUser(nullptr),
	retourPagePrincipale(nullptr),
	player(playerPrincipal)
{
	fenetreInit();
}

FenetrePointage::FenetrePointage(QObject* fenetreArrivante, Player* playerPrincipal) :
	QWidget(),
	layout(nullptr),
	usernameTitre(nullptr),
	positionTitreJoueur(nullptr),
	highscoreTitre(nullptr),
	scoreJoueur(nullptr),
	votreScore(nullptr),
	nomJoueur(nullptr),
	nomTitre(nullptr),
	scoreTitre(nullptr),
	positionJoueur(nullptr),
	positionTitre(nullptr),
	position(nullptr),
	name(nullptr),
	score(nullptr),
	highscore(nullptr),
	groupBoxScore(nullptr),
	groupBoxUser(nullptr),
	gridScore(nullptr),
	gridScoreUser(nullptr),
	retourPagePrincipale(nullptr),
	player(playerPrincipal)
{	
	fenetreInit();
	QObject::connect(this, SIGNAL(signalClosingFenetrePointage()), fenetreArrivante, SLOT(slotPourEnableFenetre()));

}

FenetrePointage::~FenetrePointage()
{

}

void FenetrePointage::fenetreInit() {
	loadHighscore(); // load histoirique des scores
	QIcon iconeHautPage;
	iconeHautPage.addPixmap(QPixmap("icon-cercle.png"));
	setWindowIcon(iconeHautPage);
	setWindowTitle("Tetris");
	setFixedSize(300, 500);
	//Pour les info du joueur
	//Pour Username
	nomJoueur = new QLabel(QString::fromStdString(player->getUsername()));
	nomJoueur->setStyleSheet("background : transparent; color:white;");
	nomJoueur->setAlignment(Qt::AlignCenter);

	//Pour score du joueur
	scoreJoueur = new QLabel(QString::number(player->getScore()));
	scoreJoueur->setStyleSheet("background : transparent; color:white; border-left : 1px solid yellow;");
	scoreJoueur->setAlignment(Qt::AlignCenter);

	//Pour Position du joueur
	positionJoueur = new QLabel("0");
	positionJoueur->setStyleSheet("background : transparent; color:white; border-right : 1px solid yellow;");
	positionJoueur->setAlignment(Qt::AlignCenter);

	//Pour la table des scores
	//Créer tous les labels avec les personnes dedans (une fois qu'ils seront lus mettre les strings dans les labels)

	name = new QLabel * [10];
	score = new QLabel * [10];
	position = new QLabel * [10];

	for (int i = 0; i < historique.size(); i++) {
		name[i] = new QLabel(QString::fromStdString(historique[i]->getUsername()));
		name[i]->setStyleSheet("background : transparent; color: white;");
		name[i]->setAlignment(Qt::AlignCenter);

		score[i] = new QLabel(QString::number(historique[i]->getScore()));
		score[i]->setStyleSheet("background : transparent; color: white; border-left : 1px solid yellow;");
		score[i]->setAlignment(Qt::AlignCenter);

		position[i] = new QLabel(QString::number(i + 1));
		position[i]->setStyleSheet("background : transparent; color: white; border-right : 1px solid yellow;");
		position[i]->setAlignment(Qt::AlignCenter);
	}

	//Déclaration Score+Username
	usernameTitre = new QLabel("Username");
	usernameTitre->setStyleSheet("background : transparent; color: white; font: bold; font-size: 15px; border-bottom: 1px solid yellow;");
	usernameTitre->setAlignment(Qt::AlignCenter);

	positionTitreJoueur = new QLabel("Position");
	positionTitreJoueur->setStyleSheet("background : transparent; color: white; font: bold; font-size: 15px; border-bottom: 1px solid yellow;");
	positionTitreJoueur->setAlignment(Qt::AlignCenter);

	highscoreTitre = new QLabel("Score");
	highscoreTitre->setStyleSheet("background : transparent; color: white; font: bold; font-size: 15px; border-bottom: 1px solid yellow;");
	highscoreTitre->setAlignment(Qt::AlignCenter);

	votreScore = new QLabel("Your Score");
	votreScore->setStyleSheet("background : transparent; color: white; font-size: 25px; font: bold;");
	votreScore->setAlignment(Qt::AlignCenter);

	//Déclaration Highscore
	nomTitre = new QLabel("Username");
	nomTitre->setStyleSheet("background : transparent; font: bold; font-size: 15px; border-bottom: 1px solid yellow;");
	nomTitre->setAlignment(Qt::AlignCenter);

	positionTitre = new QLabel("Position");
	positionTitre->setStyleSheet("background : transparent; color: white; font: bold; font-size: 15px; border-bottom: 1px solid yellow;");
	positionTitre->setAlignment(Qt::AlignCenter);

	scoreTitre = new QLabel("Score");
	scoreTitre->setStyleSheet("background : transparent; color: white; font: bold; font-size: 15px; border-bottom: 1px solid yellow;");
	scoreTitre->setAlignment(Qt::AlignCenter);


	highscore = new QLabel("HIGHSCORE");
	highscore->setStyleSheet("background : transparent; color:white; font-size: 36px; font: bold");
	highscore->setAlignment(Qt::AlignCenter);


	layout = new QVBoxLayout();

	groupBoxScore = new QGroupBox();
	groupBoxScore->setStyleSheet("background-image: url(background.png); color: white;");

	gridScore = new QGridLayout();

	groupBoxUser = new QGroupBox();
	groupBoxUser->setStyleSheet("background-image: url(background.png); color: white;");

	gridScoreUser = new QGridLayout();

	//Affichage du Score du joueur
	gridScoreUser->addWidget(votreScore, 0, 0, 1, 3, Qt::AlignCenter);
	gridScoreUser->addWidget(positionTitreJoueur, 1, 0);
	gridScoreUser->addWidget(highscoreTitre, 1, 2);
	gridScoreUser->addWidget(usernameTitre, 1, 1);
	gridScoreUser->addWidget(positionJoueur, 2, 0);
	gridScoreUser->addWidget(scoreJoueur, 2, 2);
	gridScoreUser->addWidget(nomJoueur, 2, 1);
	groupBoxUser->setLayout(gridScoreUser);

	//Affichade de la Table des Scores
	gridScore->addWidget(highscore, 0, 0, 1, 3, Qt::AlignCenter);
	gridScore->addWidget(positionTitre, 1, 0);
	gridScore->addWidget(scoreTitre, 1, 2);
	gridScore->addWidget(nomTitre, 1, 1);

	for (int i = 0; i < historique.size(); i++)
	{
		gridScore->addWidget(position[i], i + 2, 0);
		gridScore->addWidget(name[i], i + 2, 1);
		gridScore->addWidget(score[i], i + 2, 2);

	}

	groupBoxScore->setLayout(gridScore);
	layout->addWidget(groupBoxScore);
	layout->addWidget(groupBoxUser);
	this->setLayout(layout);

	QObject::connect(player, SIGNAL(scoreChanged()), this, SLOT(updateScore()));
}

Player* FenetrePointage::getNextBestScore()
{
	for (int w = 0; w < historique.size(); w++)
	{
		if (player->getScore() >= historique[w]->getScore())
		{
			if (w - 1 > -1)
			{
				return historique[w - 1];
			}

			return player;
		}
	}
	return historique[historique.size() - 1];
}	

void FenetrePointage::checkerScore() {
	bool isPlusGrand = false;
	int i = 0;
	nomJoueur->setText(QString::fromStdString(player->getUsername()));
	scoreJoueur->setText(QString::number(player->getScore()));
	positionJoueur->setText(QString::number(0));

	while ((!isPlusGrand) && (i < historique.size() - 1))
	{
		if (historique[i]->getScore() <= player->getScore())
		{
			positionJoueur->setText(QString::number(i + 1));
			for (int w = historique.size() - 1; w >= i + 1; w--) {
				historique[w]->setScore(historique[w - 1]->getScore());
				historique[w]->setUsername(historique[w - 1]->getUsername());
			}

			historique[i]->setScore(player->getScore());
			historique[i]->setUsername(player->getUsername());
			isPlusGrand = true;
		}
		i++;
	}

	if (isPlusGrand)
	{
		if (historique.size() > 10) {
			historique.pop_back();
		}
		
		for (int i = 0; i < historique.size(); i++) {
			name[i]->setText(QString::fromStdString(historique[i]->getUsername()));
			score[i]->setText(QString::number(historique[i]->getScore()));
			position[i]->setText(QString::number(i + 1));
		}

		qApp->processEvents();
	}
}

void FenetrePointage::writeHighscore() {
	std::ofstream myfile;
	myfile.open("Score.txt", std::ofstream::out | std::ofstream::trunc);

	for (int j = 0; j < historique.size(); j++)
	{
		myfile << historique[j]->getUsername() << " " << historique[j]->getScore() << std::endl;
	}

	myfile.close();
}

void FenetrePointage::loadHighscore() {
	if (historique.size() > 0) {
		historique.clear();
	}
	
	//Ouvrir document 
	std::fstream myfile;
	myfile.open("Score.txt");
	std::string line;
	std::string username;
	int score;

	if (myfile.is_open())
	{
		while (myfile >> username >> score)
		{
			Player *p = new Player(score, username);
			historique.push_back(p);
		}
	}
	myfile.close();
}

void FenetrePointage::updateScore() {
	scoreJoueur->setText(QString::number(player->getScore()));
	qApp->processEvents();
}

void FenetrePointage::closeEvent(QCloseEvent* event)
{
	emit signalClosingFenetrePointage();
}

void FenetrePointage::setJoueurUsername()
{
	nomJoueur->setText(QString::fromStdString(player->getUsername()));
}