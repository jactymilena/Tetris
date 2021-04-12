#include "FenetrePointage.h"
#include "FenetrePrincipale.h"

FenetrePointage::FenetrePointage(QObject* fenetreArrivante) :
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
	retourPagePrincipale(nullptr)
{
	joueur1.setScore(10000);

	//Pour les info du joueur
	//Pour Username
	nomJoueur = new QLabel(QString::fromStdString(joueur1.getUsername()));

	//Pour score du joueur
	scoreJoueur = new QLabel(QString::number(joueur1.getScore()));

	//Pour Position du joueur
	positionJoueur = new QLabel("x");
	//Pour la table des scores
	//Créer tous les labels avec les personnes dedans (une fois qu'ils seront lus mettre les strings dans les labels)

	name = new QLabel * [10];
	score = new QLabel * [10];
	position = new QLabel * [10];

	for (int i = 0; i < 10; i++) {
		name[i] = new QLabel();
		score[i] = new QLabel();
		position[i] = new QLabel(QString::number(i));
	}

	name[0] = new QLabel("Smokey");
	score[0] = new QLabel("500 000");

	name[1] = new QLabel("Kojima");
	score[1] = new QLabel("100 000");

	name[1] = new QLabel("Dio");
	score[1] = new QLabel("89 000");

	name[2] = new QLabel("Santa");
	score[2] = new QLabel("9 000");

	name[3] = new QLabel("Hannibal");
	score[3] = new QLabel("2 000");

	name[4] = new QLabel("Jekyll");
	score[4] = new QLabel("1 500");

	name[5] = new QLabel("Hyde");
	score[5] = new QLabel("1 000");

	name[6] = new QLabel("Bob");
	score[6] = new QLabel("100");

	name[7] = new QLabel("Legarsdurappport");
	score[7] = new QLabel("60");

	name[8] = new QLabel("Bobette");
	score[8] = new QLabel("10");

	name[9] = new QLabel("Simon");
	score[9] = new QLabel("0");

	//Pour l'affichage
	usernameTitre = new QLabel("Nom");
	positionTitreJoueur = new QLabel("Pos");
	highscoreTitre = new QLabel("Score");
	votreScore = new QLabel("Votre Score");

	nomTitre = new QLabel("Nom");
	positionTitre = new QLabel("Position");
	scoreTitre = new QLabel("Score");
	highscore = new QLabel("HIGHSCORE");


	layout = new QVBoxLayout();

	groupBoxScore = new QGroupBox();
	gridScore = new QGridLayout();

	groupBoxUser = new QGroupBox();
	gridScoreUser = new QGridLayout();

	//Pour le score du joueur
	gridScoreUser->addWidget(votreScore, 0, 0, 1, 3, Qt::AlignCenter);
	gridScoreUser->addWidget(positionTitreJoueur, 1, 0);
	gridScoreUser->addWidget(highscoreTitre, 1, 1);
	gridScoreUser->addWidget(usernameTitre, 1, 2);

	gridScoreUser->addWidget(positionJoueur, 2, 0);
	gridScoreUser->addWidget(scoreJoueur, 2, 1);
	gridScoreUser->addWidget(nomJoueur, 2, 2);

	groupBoxUser->setLayout(gridScoreUser);

	//Pour la table des scores

	gridScore->addWidget(highscore, 0, 0, 1, 3, Qt::AlignCenter);
	gridScore->addWidget(positionTitre, 1, 0);
	gridScore->addWidget(scoreTitre, 1, 1);
	gridScore->addWidget(nomTitre, 1, 2);

	for (int i = 0; i < 10; i++)
	{
		gridScore->addWidget(position[i], i + 2, 0);
		gridScore->addWidget(score[i], i + 2, 1);
		gridScore->addWidget(name[i], i + 2, 2);
	}

	groupBoxScore->setLayout(gridScore);

	layout->addWidget(groupBoxScore);
	layout->addWidget(groupBoxUser);

	this->setLayout(layout);

	QObject::connect(this, SIGNAL(signalClosingFenetrePointage()), fenetreArrivante, SLOT(slotPourEnableFenetre()));

}
FenetrePointage::~FenetrePointage()
{

}

void FenetrePointage::closeEvent(QCloseEvent* event)
{
	emit signalClosingFenetrePointage();
}

void FenetrePointage::setJoueurUsername(std::string username)
{
	joueur1.setUsername(username);
	nomJoueur->setText(QString::fromStdString(username));
}
