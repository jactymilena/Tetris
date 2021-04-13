#include "FenetreDeJeu.h"


FenetreDeJeu::FenetreDeJeu(QMainWindow* fenetrePrincipale, Player* playerPrincipal) : 
m_menuMenu(nullptr), m_menuBar(nullptr), m_menuOptionAccueil(nullptr), m_menuOptionQuitter(nullptr), player(playerPrincipal),
m_widget(nullptr), m_layout(nullptr), m_Garder(nullptr), m_hold(nullptr), m_gauche(nullptr), m_layoutGauche(nullptr),
m_centre(nullptr), m_droite(nullptr), m_gaucheHold(nullptr), m_Test(nullptr), m_bar(nullptr), m_layoutCentre(nullptr), m_tetris(nullptr),
m_layoutScore(nullptr), m_scoreBox(nullptr), m_score(nullptr), m_bestscore(nullptr), m_joueur(nullptr), m_level(nullptr), m_layoutDroite(nullptr), 
m_elevel(nullptr), m_pnext(nullptr), m_holdnext(nullptr), m_fenetrePointage(nullptr), m_gameOverLayout(nullptr), m_gameOverWidget(nullptr),
m_recommencerButton(nullptr), m_gameOverQuitterButton(nullptr), m_menuOptionAide(nullptr), frameHold(nullptr), framePieceSuivante(nullptr),
m_prochainScore(nullptr), m_prochainIndividu(nullptr)
{
	// Background
	//setStyleSheet("background-image: url(background.png)");
	setStyleSheet("background-color: red");


	m_layout = new QHBoxLayout();
	m_widget = new QWidget();
	board = new Board(this, playerPrincipal);
	frameHold = new FramePourPiece((board->getPieceHold()));
	framePieceSuivante = new FramePourPiece((board->getPieceSuivante()));
	//Partie Gauche
	m_gauche = new QGroupBox(tr("Gauche"));
	m_gauche->setStyleSheet("QGroupBox { background : transparent;}");
	m_gaucheHold = new QGroupBox(tr("Hold"));
	m_gaucheHold->setStyleSheet("QGroupBox { background : transparent;}");
	m_layoutGauche = new QVBoxLayout();
	m_Garder = new QLabel("Garder");
	m_hold = new QGridLayout;
	m_Test = new QLabel("Test");
	m_Garder->setAlignment(Qt::AlignLeft);
	m_hold->setAlignment(Qt::AlignLeft);
	m_hold->addWidget(frameHold, 0, 0);
	m_gaucheHold->setLayout(m_hold);
	m_layoutGauche->addWidget(m_Garder);
	m_layoutGauche->addWidget(m_gaucheHold);
	m_gauche->setLayout(m_layoutGauche);
	m_layout->addWidget(m_gauche);

	//Partie Centre 
	m_centre = new QGroupBox(tr("Next"));
	m_centre->setStyleSheet("QGroupBox { background : transparent;}");
	m_console = new QGroupBox(tr("Tetris"));
	m_console->setStyleSheet("QGroupBox { background : transparent;}");
	m_progressBarBox = new QGroupBox();

	m_layoutProgressBar = new QGridLayout();
	m_layoutCentre = new QVBoxLayout();
	m_bar = new QProgressBar();
	m_bar->setMinimum(0);
	m_bar->setMaximum(100);
	m_bar->setMinimumWidth(200);
	m_tetris = new QVBoxLayout;
	m_level = new QLabel(QString::number(player->getLevel()));
	m_nextLevel = new QLabel(QString::number(player->getLevel() + 1));
	QObject::connect(player, SIGNAL(levelChanged()), this, SLOT(updateLevel()));

	m_layoutProgressBar->addWidget(m_level, 0, 0, Qt::AlignLeft);
	m_layoutProgressBar->addWidget(m_nextLevel,0, 2, Qt::AlignLeft);
	m_layoutProgressBar->addWidget(m_bar, 1, 1, 1, 1);

	boardInit(); // mettre au centre

	m_console->setLayout(m_tetris);
	m_progressBarBox->setLayout(m_layoutProgressBar);
	m_layoutCentre->addWidget(m_progressBarBox);
	m_layoutCentre->addWidget(m_console);
	m_centre->setLayout(m_layoutCentre);
	m_layout->addWidget(m_centre);

	//Partie Droite
	m_lcdScore = new QLCDNumber(this);
	m_lcdScore->setSegmentStyle(QLCDNumber::Filled);
	m_lcdScore->display(player->getScore());
	QObject::connect(player, SIGNAL(scoreChanged()),this ,SLOT(updateScore()));

	m_droite = new QGroupBox(tr("Droite"));
	m_droite->setStyleSheet("QGroupBox { background : transparent;}");

	m_holdnext = new QGroupBox(tr("Next"));
	m_holdnext->setStyleSheet("QGroupBox { background : transparent;}");

	m_scoreBox = new QGroupBox();
	m_scoreBox->setStyleSheet("QGroupBox { background : transparent;}");

	m_pnext = new QGridLayout;
	m_layoutDroite = new QVBoxLayout();
	m_layoutScore = new QVBoxLayout();
	m_elevel = new QProgressBar();
	m_score = new QLabel("SCORE");
	m_bestscore = new QLabel("Next meilleur score");
	m_joueur = new QLabel("Joueur");
	m_fenetrePointage = new FenetrePointage(player);
	nextBestPlayer = new Player();
	nextBestPlayer = (m_fenetrePointage->getNextBestScore());
	m_prochainScore = new QLabel(QString::number(nextBestPlayer->getScore()));
	m_prochainIndividu = new QLabel(QString::fromStdString(nextBestPlayer->getUsername()));




	m_layoutScore->addWidget(m_score);
	m_layoutScore->addWidget(m_score);
	m_layoutScore->addWidget(m_lcdScore);

	m_scoreBox->setLayout(m_layoutScore);
	m_holdnext->setLayout(m_pnext);
	m_layoutDroite->addWidget(framePieceSuivante);
	m_layoutDroite->addWidget(m_scoreBox);
	m_layoutDroite->addWidget(m_holdnext);
	m_layoutDroite->addWidget(m_bestscore);
	m_layoutDroite->addWidget(m_joueur);
	m_layoutDroite->addWidget(m_elevel);
	m_layoutDroite->addWidget(m_prochainIndividu);
	m_layoutDroite->addWidget(m_prochainScore);
	m_droite->setLayout(m_layoutDroite);
	m_layout->addWidget(m_droite);

	//Onglet Menu + Aide
	m_menuBar = new QMenuBar;
	m_menuMenu = new QMenu("Menu");
	m_menuBar->addMenu(m_menuMenu);
	m_menuOptionAccueil = new QAction("Accueil");
	m_menuOptionQuitter = new QAction("Quitter");
	m_menuOptionAide = new QAction("Aide");
	m_menuMenu->addAction(m_menuOptionAccueil);
	m_menuMenu->addAction(m_menuOptionQuitter);
	m_menuMenu->addAction(m_menuOptionAide);
	m_layout->setMenuBar(m_menuBar);

	//Action 
	QObject::connect(m_menuOptionAccueil, SIGNAL(triggered(bool)), this, SLOT(slotPourFenetrePrincipale()));
	QObject::connect(this, SIGNAL(signalRetourPrincipale()), fenetrePrincipale, SLOT(slotChangerFenetrePrincipale()));
	QObject::connect(m_menuOptionAide, SIGNAL(triggered(bool)), this, SLOT(slotPourFenetreAide()));
	QObject::connect(this, SIGNAL(signalAllerAide()), fenetrePrincipale, SLOT(slotChangerFenetreAide()));
	QObject::connect(m_menuOptionQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));


	setLayout(m_layout);

	// Game over widget
	m_gameOverLayout = new QVBoxLayout();

	m_gameOverQuitterButton = new QPushButton("Quitter");
	m_recommencerButton = new QPushButton("Recommencer");
	QObject::connect(m_gameOverQuitterButton, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
	QObject::connect(m_recommencerButton, SIGNAL(clicked(bool)), this, SLOT(recommencerBoard()));

	
	m_gameOverLayout->addWidget(m_fenetrePointage);
	m_gameOverLayout->addWidget(m_recommencerButton);
	m_gameOverLayout->addWidget(m_gameOverQuitterButton);

	m_gameOverWidget = new QWidget();
	m_gameOverWidget->setLayout(m_gameOverLayout);
}

void FenetreDeJeu::slotGameOver() {
	m_fenetrePointage->checkerScore();
	this->setEnabled(false);
	m_gameOverWidget->show();
}

void FenetreDeJeu::recommencerBoard() {
	board->restart();
	this->setEnabled(true);
	m_gameOverWidget->hide();
}

void FenetreDeJeu::updateScore() {
	m_lcdScore->display(player->getScore());
	m_bar->setValue(player->getScore() % 100);
	nextBestPlayer = (m_fenetrePointage->getNextBestScore());
	m_prochainScore->setText(QString::number(nextBestPlayer->getScore()));
	m_prochainIndividu->setText(QString::fromStdString(nextBestPlayer->getUsername()));
}

void FenetreDeJeu::updateLevel() {
	m_level->setText(QString::number(player->getLevel()));
	m_nextLevel->setText(QString::number(player->getLevel() + 1));
	qApp->processEvents();
}

void FenetreDeJeu::slotPourFenetrePrincipale()
{
	emit signalRetourPrincipale();
}

void FenetreDeJeu::slotPourFenetreAide()
{
	emit signalAllerAide();
}


void FenetreDeJeu::boardInit() {
	board = new Board(this, player);
	board->setFocus();
	board->setFocusPolicy(Qt::StrongFocus);
	QObject::connect(board, SIGNAL(gameOverSignal()), this, SLOT(slotGameOver()));
	m_tetris->addWidget(board);
}

FenetreDeJeu::~FenetreDeJeu()
{
	close();
}

void FenetreDeJeu::slotPourTrigeredHold()
{
	frameHold->setPiece(board->getPieceHold());
}

void FenetreDeJeu::slotPourTrigeredSuivante()
{
	framePieceSuivante->setPiece(board->getPieceSuivante());
}