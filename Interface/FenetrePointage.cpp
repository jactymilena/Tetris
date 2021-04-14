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
	fenetreInit(player);
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
	fenetreInit(player);
	QObject::connect(this, SIGNAL(signalClosingFenetrePointage()), fenetreArrivante, SLOT(slotPourEnableFenetre()));

}

FenetrePointage::~FenetrePointage()
{
	for (auto player : historique) {
		delete player;
	}
	historique.clear();
}

void FenetrePointage::fenetreInit(Player* player) {
	loadHighscore(); // load histoirique des scores

	//Pour les info du joueur
	//Pour Username
	nomJoueur = new QLabel(QString::fromStdString(player->getUsername()));

	//Pour score du joueur
	scoreJoueur = new QLabel(QString::number(player->getScore()));

	//Pour Position du joueur
	positionJoueur = new QLabel("0");
	//Pour la table des scores
	//Créer tous les labels avec les personnes dedans (une fois qu'ils seront lus mettre les strings dans les labels)

	name = new QLabel * [10];
	score = new QLabel * [10];
	position = new QLabel * [10];

	for (int i = 0; i < historique.size(); i++) {
		name[i] = new QLabel(QString::fromStdString(historique[i]->getUsername()));
		score[i] = new QLabel(QString::number(historique[i]->getScore()));
		position[i] = new QLabel(QString::number(i + 1));
	}

	//Déclaration Score+Username
	usernameTitre = new QLabel("Nom");
	positionTitreJoueur = new QLabel("Pos");
	highscoreTitre = new QLabel("Score");
	votreScore = new QLabel("Votre Score");

	//Déclaration Highscore
	nomTitre = new QLabel("Nom");
	positionTitre = new QLabel("Position");
	scoreTitre = new QLabel("Score");
	highscore = new QLabel("HIGHSCORE");


	layout = new QVBoxLayout();

	groupBoxScore = new QGroupBox();
	gridScore = new QGridLayout();

	groupBoxUser = new QGroupBox();
	gridScoreUser = new QGridLayout();

	//Affichage du Score du joueur
	gridScoreUser->addWidget(votreScore, 0, 0, 1, 3, Qt::AlignCenter);
	gridScoreUser->addWidget(positionTitreJoueur, 1, 0);
	gridScoreUser->addWidget(highscoreTitre, 1, 1);
	gridScoreUser->addWidget(usernameTitre, 1, 2);
	gridScoreUser->addWidget(positionJoueur, 2, 0);
	gridScoreUser->addWidget(scoreJoueur, 2, 1);
	gridScoreUser->addWidget(nomJoueur, 2, 2);
	groupBoxUser->setLayout(gridScoreUser);

	//Affichade de la Table des Scores
	gridScore->addWidget(highscore, 0, 0, 1, 3, Qt::AlignCenter);
	gridScore->addWidget(positionTitre, 1, 0);
	gridScore->addWidget(scoreTitre, 1, 1);
	gridScore->addWidget(nomTitre, 1, 2);

	for (int i = 0; i < historique.size(); i++)
	{
		gridScore->addWidget(position[i], i + 2, 0);
		gridScore->addWidget(score[i], i + 2, 1);
		gridScore->addWidget(name[i], i + 2, 2);
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

	while ((!isPlusGrand) && (i < historique.size() - 1))
	{
		if (historique[i]->getScore() <= player->getScore())
		{
			positionJoueur->setText(QString::number(i));
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
		std::ofstream myfile;
		myfile.open("Score.txt", std::ofstream::out | std::ofstream::trunc);

		for (int j = 0; j < historique.size(); j++)
		{
			myfile << historique[j]->getUsername() << " " << historique[j]->getScore() << std::endl;
		}

		myfile.close();

		for (int i = 0; i < historique.size(); i++) {
			name[i]->setText(QString::fromStdString(historique[i]->getUsername()));
			score[i]->setText(QString::number(historique[i]->getScore()));
			position[i]->setText(QString::number(i + 1));
		}
		qApp->processEvents();
	}
}

void FenetrePointage::loadHighscore() {
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