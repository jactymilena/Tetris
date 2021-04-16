/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: FenetreDeJeu.h
Date:           15 avril 2021
But:            Affiche le board ainsi que ces intéractions
====================================*/

#include "FenetreDeJeu.h"

FenetreDeJeu::FenetreDeJeu(QMainWindow* fenetrePrincipale, Player* playerPrincipal) : 
m_menuMenu(nullptr), m_menuBar(nullptr), m_menuOptionAccueil(nullptr), m_menuOptionQuitter(nullptr), player(playerPrincipal),
m_widget(nullptr), m_layout(nullptr), m_usernameLabel(nullptr), m_hold(nullptr), m_gauche(nullptr), m_layoutGauche(nullptr),
m_centre(nullptr), m_droite(nullptr), m_gaucheHold(nullptr), m_holdLabel(nullptr), m_bar(nullptr), m_layoutCentre(nullptr), m_tetris(nullptr),
m_layoutScore(nullptr), m_scoreBox(nullptr), m_score(nullptr), m_bestscore(nullptr), m_joueur(nullptr), m_level(nullptr), m_layoutDroite(nullptr), 
m_elevel(nullptr), m_pnext(nullptr), m_holdnext(nullptr), m_fenetrePointage(nullptr), m_gameOverLayout(nullptr), m_gameOverWidget(nullptr),
m_recommencerButton(nullptr), m_gameOverQuitterButton(nullptr), m_menuOptionAide(nullptr), frameHold(nullptr), framePieceSuivante(nullptr),
m_prochainScore(nullptr), m_prochainIndividu(nullptr)
{
	m_layout = new QHBoxLayout();
	m_widget = new QWidget();
	board = new Board(this, playerPrincipal);
	frameHold = new FramePourPiece((board->getPieceHold()));
	framePieceSuivante = new FramePourPiece((board->getPieceSuivante()));

	//Partie Gauche
	
	//Username
	m_layoutUsername = new QVBoxLayout();
	m_layoutUsername->setSpacing(0);
	m_usernameTitle = new QLabel("Username");
	m_usernameTitle->setStyleSheet("background : transparent; color: white; font: bold; font-size: 35px;");
	m_usernameLabel = new QLabel();
	m_usernameLabel->setStyleSheet("background : transparent; color: white; font: italic; font-size: 20px;");
	m_layoutUsername->addWidget(m_usernameTitle, 0, Qt::AlignBottom);
	m_layoutUsername->addWidget(m_usernameLabel, 0, Qt::AlignTop);
	m_usernameBox = new QGroupBox();
	m_usernameBox->setStyleSheet("QGroupBox { background : transparent; border: none}");
	m_usernameBox->setLayout(m_layoutUsername);

	//Hold
	m_gauche = new QGroupBox();
	m_gauche->setStyleSheet("QGroupBox { background : transparent; border: none}");
	m_gaucheHold = new QGroupBox();
	m_gaucheHold->setStyleSheet("QGroupBox { background : transparent;}");
	m_layoutGauche = new QVBoxLayout();
	m_hold = new QGridLayout;
	m_holdLabel = new QLabel("Hold");
	m_holdLabel->setStyleSheet("background : transparent; color: white; font-size: 36px; font: bold;");
	m_usernameLabel->setAlignment(Qt::AlignLeft);
	m_hold->setAlignment(Qt::AlignLeft);
	m_hold->addWidget(m_holdLabel, 0, 0);
	m_hold->addWidget(frameHold, 1, 0);
	m_gaucheHold->setLayout(m_hold);
	m_layoutGauche->addWidget(m_usernameBox);
	m_layoutGauche->addWidget(m_gaucheHold);
	m_gauche->setLayout(m_layoutGauche);
	m_layout->addWidget(m_gauche);

	//Partie Centre 
	///Création GroupBox
	m_centre = new QGroupBox();
	m_console = new QGroupBox(tr("Tetris"));
	m_progressBarBox = new QGroupBox();
	///Attribution de Style au GroupBox
	m_centre->setStyleSheet("QGroupBox { background : transparent; border: none;}");
	m_console->setStyleSheet("QGroupBox { background : transparent;}");
	m_progressBarBox->setFixedHeight(50);
	m_progressBarBox->setStyleSheet("QGroupBox { background : transparent; border: 2px solid white;}");
	///Création de Layout
	m_layoutProgressBar = new QGridLayout();
	m_layoutCentre = new QVBoxLayout();
	m_tetris = new QVBoxLayout;
	///Création ProgessBar
	m_bar = new QProgressBar();
	///Attribution de Style ProgressBar
	m_bar->setStyleSheet("QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #05B8CC,stop: 0.4999 #05a4cc,stop: 0.5 #05a4cc,stop: 1 #0551cc );border-radius: 5px; border: 2px solid black;} QProgressBar { border: 2px solid white; border-radius: 5px; background: transparent; text-align: center; color: white }");
	//m_bar->setStyleSheet("QProgressBar::chunk { background-color: #2196F3; width: 10px; margin: 0.5px } QProgressBar { border: 2px solid white; border-radius: 5px; background: transparent; text-align: center; color: white }");
	m_bar->setMinimum(0);
	m_bar->setMaximum(100);
	m_bar->setMinimumWidth(200);
	
	///Création Label
	m_level = new QLabel(QString::number(player->getLevel()));
	m_nextLevel = new QLabel(QString::number(player->getLevel() + 1));
	///Attribution de Style Label
	m_level->setStyleSheet("QLabel{background : transparent; color: white; font-size: 20px;}");
	m_nextLevel->setStyleSheet("background : transparent; color: white; font-size: 20px;");
	///Actions
	QObject::connect(player, SIGNAL(levelChanged()), this, SLOT(updateLevel()));
	///Ajout au Layout Central
	m_layoutProgressBar->addWidget(m_level, 0, 0, Qt::AlignLeft);
	m_layoutProgressBar->addWidget(m_nextLevel,0, 2, Qt::AlignLeft);
	m_layoutProgressBar->addWidget(m_bar, 0, 1);

	boardInit(); // Mettre au centre

	///Attribution au Layout
	m_console->setLayout(m_tetris);
	m_progressBarBox->setLayout(m_layoutProgressBar);
	m_layoutCentre->addWidget(m_progressBarBox, Qt::AlignTop);
	m_layoutCentre->addWidget(m_console);
	m_centre->setLayout(m_layoutCentre);
	m_layout->addWidget(m_centre);

	//Partie Droite
	///Création de Label + Style
	m_nextLabel = new QLabel("Next");
	m_nextLabel->setStyleSheet("background : transparent; color: white; font-size: 36px; font: bold;");
	m_nextLabel->setFixedHeight(40);

	m_score = new QLabel("SCORE");
	m_score->setMinimumHeight(30);
	m_score->setStyleSheet("background : transparent; font-size: 20px; font: bold; color: black;");
	//Création de LCDnumber + Style
	m_lcdScore = new QLCDNumber(this);
	m_lcdScore->setMinimumHeight(40);
	m_lcdScore->setStyleSheet("background : transparent;");
	m_lcdScore->setSegmentStyle(QLCDNumber::Filled);
	m_lcdScore->display(player->getScore());
	///Action
	QObject::connect(player, SIGNAL(scoreChanged()),this ,SLOT(updateScore()));

	///Création de GroupBox + Style
	m_droite = new QGroupBox();
	m_droite->setStyleSheet("QGroupBox { background : transparent; border: none;}");

	m_holdnext = new QGroupBox(tr("Next"));
	m_holdnext->setStyleSheet("QGroupBox { background : transparent; border: none}");

	m_scoreBox = new QGroupBox();
	m_scoreBox->setMaximumHeight(60);
	m_scoreBox->setStyleSheet("QGroupBox { background : rgba(170, 170, 170, 128);}");

	///Prochain meilleur
	m_userIconLabel = new QLabel();
	m_userIcon = new QPixmap("user-icon-white.png");
	//m_userIcon->setStyleSheet(" { background : transparent;}");
	m_userIconLabel->setPixmap(*m_userIcon);
	m_userIconLabel->setAlignment(Qt::AlignCenter);
	m_userIconLabel->setStyleSheet("background : transparent;");

	///Création de Layout
	m_pnext = new QGridLayout;
	m_layoutDroite = new QVBoxLayout();
	m_layoutScore = new QHBoxLayout();
	///Création de ProgressBar
	m_elevel = new QProgressBar();
	m_elevel->setStyleSheet("QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #05B8CC,stop: 0.4999 #05a4cc,stop: 0.5 #05a4cc,stop: 1 #0551cc );border-radius: 5px; border: 2px solid black;} QProgressBar { border: 2px solid white; border-radius: 5px; background: transparent; text-align: center; color: white }");
	m_elevel->setMinimum(0);
	m_elevel ->setMaximum(100);
	m_elevel->setMinimumWidth(200);

	m_bestscore = new QLabel("Next best score");
	m_bestscore->setStyleSheet("background :  rgba(170, 170, 170, 128); color: white; font-size: 25px; font: bold;");
	m_bestscore->setAlignment(Qt::AlignCenter);

	m_joueur = new QLabel("Joueur");
	m_joueur->setStyleSheet("background : transparent;");

	m_nextBestPlayerBox = new QGroupBox();
	m_nextBestPlayerBox->setStyleSheet("QGroupBox { background : transparent; border: 2px solid white;}");
	m_layoutBestPlayer = new QVBoxLayout();

	m_fenetrePointage = new FenetrePointage(player);
	nextBestPlayer = new Player();
	nextBestPlayer = (m_fenetrePointage->getNextBestScore());

	m_prochainScore = new QLabel(QString::number(nextBestPlayer->getScore()));
	m_prochainScore->setStyleSheet("background : transparent; color: white; font-size: 25px; font: bold;");
	m_prochainScore->setAlignment(Qt::AlignCenter);

	m_prochainIndividu = new QLabel(QString::fromStdString(nextBestPlayer->getUsername()));
	m_prochainIndividu->setStyleSheet("background : transparent; color: white; font-size: 18px; font: bold;");
	m_prochainIndividu->setAlignment(Qt::AlignCenter);

	m_layoutBestPlayer->addWidget(m_bestscore);
	m_layoutBestPlayer->addWidget(m_prochainIndividu);
	m_layoutBestPlayer->addWidget(m_userIconLabel);
	m_layoutBestPlayer->addWidget(m_elevel);
	m_layoutBestPlayer->addWidget(m_prochainScore);
	m_nextBestPlayerBox->setLayout(m_layoutBestPlayer);


	m_layoutScore->addWidget(m_score);
	m_layoutScore->addWidget(m_lcdScore, Qt::AlignCenter);
	m_pnext->addWidget(m_nextLabel, 0, 0);
	m_pnext->addWidget(framePieceSuivante, 1, 0);

	m_scoreBox->setLayout(m_layoutScore);
	m_holdnext->setLayout(m_pnext);
	m_layoutDroite->addWidget(m_holdnext);
	m_layoutDroite->addWidget(m_scoreBox);
	m_layoutDroite->addWidget(m_nextBestPlayerBox);
	m_droite->setLayout(m_layoutDroite);
	m_layout->addWidget(m_droite);

	//Onglet Menu + Options
	m_menuBar = new QMenuBar;
	m_menuBar->setStyleSheet("QMenuBar { background : transparent; color: white;} QMenuBar::item:selected { border: 1px solid white; } QMenuBar::item:pressed { background : black; color: white; }");
	m_menuMenu = new QMenu("Menu");
	m_menuMenu->setStyleSheet("background : transparent; color: white;");

	m_menuBar->addMenu(m_menuMenu);
	m_menuOptionAccueil = new QAction("Home");
	m_menuOptionQuitter = new QAction("Exit");
	m_menuOptionAide = new QAction("Parameters");
	m_menuMenu->addAction(m_menuOptionAccueil);
	m_menuMenu->addAction(m_menuOptionAide);
	m_menuMenu->addAction(m_menuOptionQuitter);
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
	//m_gameOverQuitterButton->setFixedWidth(200);
	m_gameOverQuitterButton->setStyleSheet("border-radius: 10px; border: 2px solid black; color: black; font: bold; background-color: #ffc72b;");
	m_recommencerButton = new QPushButton("Recommencer");
	//m_recommencerButton->setFixedWidth(200);
	m_recommencerButton->setStyleSheet("border-radius: 10px; border: 2px solid black; color: black; font: bold; background-color: #ffc72b;");
	
	QObject::connect(m_gameOverQuitterButton, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
	QObject::connect(m_recommencerButton, SIGNAL(clicked(bool)), this, SLOT(recommencerBoard()));

	m_gameOverLayout->addWidget(m_fenetrePointage);
	m_gameOverLayout->addWidget(m_recommencerButton);
	m_gameOverLayout->addWidget(m_gameOverQuitterButton, Qt::AlignCenter);

	QIcon iconeHautPage;
	iconeHautPage.addPixmap(QPixmap("icon-cercle.png"));
	
	m_gameOverWidget = new QWidget();
	m_gameOverWidget->setWindowIcon(iconeHautPage);
	m_gameOverWidget->setWindowTitle("Tetris");
	m_gameOverWidget->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	m_gameOverWidget->setLayout(m_gameOverLayout);
}

void FenetreDeJeu::setUsernameLabel() {
	m_usernameLabel->setText(QString::fromStdString(player->getUsername()));
	qApp->processEvents();
}
 
void FenetreDeJeu::slotGameOver() {
	m_fenetrePointage->checkerScore();
	m_fenetrePointage->writeHighscore();
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
	m_elevel->setValue((player->getScore() * 100) / (nextBestPlayer->getScore()));
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
	if (board->getIsStarted()) {
		board->pause();
	}
	emit signalRetourPrincipale();
}

void FenetreDeJeu::slotPourFenetreAide()
{
	if (board->getIsStarted()) {
		board->pause();
	}
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
	board->resetBoard();
	delete board;
	board = nullptr;
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