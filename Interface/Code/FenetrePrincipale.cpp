/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: FenetrePrincipale.cpp
Date: 15 avril 2021
But: Fenêtre d'accueil de l'application
====================================*/

#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale() :
	boutonPourFenetreJeu(nullptr),
	boutonPourFenetreReglage(nullptr),
	boutonPourScore(nullptr),
	labelTetris(nullptr),
	layoutVertical1(nullptr),
	widget(nullptr),
	fenetreDeJeu(nullptr),
	fenetreAide(nullptr),
	index(nullptr)
{
	index = new QStackedWidget;
	setMouseTracking(true);
	setWindowTitle("Tetris");
	//Player
	player = new Player();

	//Le titre Tetris Mania 
	labelTetris = new QLabel();
	QPixmap pixmapTitre("Tetris-logo1.png");
	labelTetris->setPixmap(pixmapTitre);
	labelTetris->setAttribute(Qt::WA_TranslucentBackground);
	QFont font = labelTetris->font();
	font.setPointSize(40);
	labelTetris->setFont(font);

	//Creation des boutons
	boutonPourFenetreJeu = new BoutonPrincipal(false);
	boutonPourFenetreJeu->setText("NEW GAME");
	boutonPourFenetreReglage = new BoutonPrincipal(false);
	boutonPourFenetreReglage->setText("PARAMETERS");
	boutonPourScore = new BoutonPrincipal(false);
	boutonPourScore->setText("SCORE");
	boutonPourQuitter = new BoutonPrincipal(false);
	boutonPourQuitter->setText("EXIT");
	boutonPourContinuer = new BoutonPrincipal(false);
	boutonPourContinuer->setText("CONTINUE");
	
	//Pointage + Dialogue(Entrer votre nom)
	fenetrePointage = new FenetrePointage(this, player);

	//Setter Un font pour le dialog
	font = QFont();
	font.setBold(true);
	font.setPointSize(20);

	QIcon iconeHautPage;
	iconeHautPage.addPixmap(QPixmap("icon-cercle.png"));

	demandeUsername = new QInputDialog();
	demandeUsername->setInputMode(QInputDialog::TextInput);
	demandeUsername->setFixedSize(200, 200);
	demandeUsername->setWindowTitle("Register");
	demandeUsername->setWindowIcon(iconeHautPage);
	demandeUsername->setLabelText("Please enter username :");
	demandeUsername->setFont(font);

	//Creation layout 
	layoutVertical1 = new QVBoxLayout();

	//Creation widget 
	widget = new QWidget();

	//Ajout au layout
	layoutVertical1->addWidget(labelTetris);
	layoutVertical1->setAlignment(labelTetris, Qt::AlignCenter);
	layoutVertical1->addWidget(boutonPourFenetreJeu);
	layoutVertical1->setAlignment(boutonPourFenetreJeu, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourContinuer);
	layoutVertical1->setAlignment(boutonPourContinuer, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourFenetreReglage);
	layoutVertical1->setAlignment(boutonPourFenetreReglage, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourScore);
	layoutVertical1->setAlignment(boutonPourScore, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourQuitter);
	layoutVertical1->setAlignment(boutonPourQuitter, Qt::AlignHCenter);

	//Ajout widget au layout
	widget->setLayout(layoutVertical1);
	setFixedSize(900, 750);
	setCentralWidget(widget);
	QObject::connect(boutonPourScore, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetrePointage()));
	fenetreDeJeu = new FenetreDeJeu(this, player);
	fenetreAide = new FenetreAide(this);
	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), SLOT(slotPourFenetreDeJeu()));
	QObject::connect(boutonPourFenetreReglage, SIGNAL(clicked(bool)), SLOT(slotChangerFenetreAide()));
	QObject::connect(boutonPourQuitter, SIGNAL(clicked(bool)), qApp, SLOT(quit()));
	QObject::connect(boutonPourContinuer, SIGNAL(clicked(bool)), this, SLOT(slotPourContinuer()));
	boutonPourContinuer->setVisible(false);
	
	//Action
	index->addWidget(widget);
	index->addWidget(fenetreDeJeu);
	index->addWidget(fenetreAide);
	setCentralWidget(index);
	index->setCurrentIndex(0);
}

FenetrePrincipale::~FenetrePrincipale()
{
}

void FenetrePrincipale::slotPourContinuer() {
	index->setCurrentIndex(1);
}

//Montre la boîte de dialogue et met la fenêtre de jeu comme centralWidget
void FenetrePrincipale::slotPourFenetreDeJeu()
{
	if (fenetreDeJeu->getGameStarted()) {
		fenetreDeJeu->recommencerBoard();
		index->setCurrentIndex(1);
	}
	else {
		if (!player->getNameSetted()) {
			bool ok;
			QString text;

			ok = demandeUsername->exec();
			text = demandeUsername->textValue();
			if (ok && !text.isEmpty())
			{
				player->setNameSetted(true);
				player->setUsername((text.simplified().remove(' ')).toStdString());
				fenetreDeJeu->setUsernameLabel();
				fenetrePointage->setJoueurUsername();
				fenetrePointage->loadHighscore();
				index->setCurrentIndex(1);
			}
		}
		else {
			index->setCurrentIndex(1);
		}
	}
	
}

//Aller à la fenêtre de paramètres
void FenetrePrincipale::slotChangerFenetreAide()
{
	index->setCurrentIndex(2);
}

//Revenir avec la fenêtre principale
void FenetrePrincipale::slotChangerFenetrePrincipale()
{
	if (fenetreDeJeu->getGameStarted()) {
		boutonPourContinuer->setVisible(true);
	}
	index->setCurrentIndex(0);
}

//Active la fenêtre
void FenetrePrincipale::slotPourEnableFenetre()
{
	this->setEnabled(true);
}

//Va à la fenêtre de pointage et montre le dialogue
void FenetrePrincipale::slotPourFenetrePointage()
{
	bool ok;
	QString text;

	if (!player->getNameSetted()) {
		ok = demandeUsername->exec();
		text = demandeUsername->textValue();

		if (!text.isEmpty() && ok)
		{
			player->setNameSetted(true);
			player->setUsername((text.simplified().remove(' ')).toStdString());
			fenetreDeJeu->setUsernameLabel();
			fenetrePointage->setJoueurUsername();
			fenetrePointage->loadHighscore();
			fenetrePointage->checkerScore();
			fenetrePointage->show();
			this->setEnabled(false);
		}
	}
	else {
		fenetrePointage->loadHighscore();
		fenetrePointage->checkerScore();
		fenetrePointage->show();
		this->setEnabled(false);
	}
}

//Ferme la fenetre de pointage et le mp3
void FenetrePrincipale::closeEvent(QCloseEvent* event)
{
	if (fenetrePointage != nullptr)
	{
		fenetrePointage->hide();
	}
	mciSendStringA("close Tetris.mp3" , nullptr, 0, nullptr);
}

