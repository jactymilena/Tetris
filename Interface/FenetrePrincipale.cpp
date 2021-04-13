#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale():
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
	boutonPourFenetreJeu = new BoutonPrincipal();
	boutonPourFenetreJeu->setText("Nouvelle Partie");
	boutonPourFenetreReglage = new BoutonPrincipal();
	boutonPourFenetreReglage->setText("Reglages");
	boutonPourScore = new BoutonPrincipal();
	boutonPourScore->setText("Pointage");
	
	
	//Pointage + Dialogue(Entrer votre nom)
	fenetrePointage = new FenetrePointage(this, player);
	demandeUsername = new QInputDialog;

	//Creation layout 
	layoutVertical1 = new QVBoxLayout();

	//Creation widget 
	widget = new QWidget();

	//Ajout au layout
	layoutVertical1->addWidget(labelTetris);
	layoutVertical1->setAlignment(labelTetris, Qt::AlignCenter);
	layoutVertical1->addWidget(boutonPourFenetreJeu);
	layoutVertical1->setAlignment(boutonPourFenetreJeu, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourFenetreReglage);
	layoutVertical1->setAlignment(boutonPourFenetreReglage, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourScore);
	layoutVertical1->setAlignment(boutonPourScore, Qt::AlignHCenter);

	//Ajout widget au layout
	widget->setLayout(layoutVertical1);
	setFixedSize(900,750);
	setStyleSheet("background-image: url(background.png)");
	setCentralWidget(widget);
	QObject::connect(boutonPourScore, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetrePointage()));
	fenetreDeJeu = new FenetreDeJeu(this, player);
	fenetreAide = new FenetreAide(this);
	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), SLOT(slotPourFenetreDeJeu()));
	
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

void FenetrePrincipale::slotPourFenetreDeJeu()
{
	if (!player->getNameSetted()) {
		bool ok;
		QString text;
	
		demandeUsername->setMinimumSize(1000, 1000);
		text = demandeUsername->getText(this, tr("Entrez votre nom"),
			tr("Username:"), QLineEdit::Normal,
			"Enter username", &ok, Qt::MSWindowsFixedSizeDialogHint);
		
		if (ok && !text.isEmpty())
		{
			player->setNameSetted(true);
			player->setUsername((text.simplified().remove(' ')).toStdString());
			fenetrePointage->setJoueurUsername();
			fenetrePointage->loadHighscore();
			index->setCurrentIndex(1);

		}
	}
	else {
		index->setCurrentIndex(1);
	}
}

void FenetrePrincipale::slotChangerFenetreAide()
{
	index->setCurrentIndex(2);
}

void FenetrePrincipale::slotChangerFenetrePrincipale()
{
	index->setCurrentIndex(0);
}

void FenetrePrincipale::slotPourEnableFenetre()
{
	this->setEnabled(true);
}

void FenetrePrincipale::slotPourFenetrePointage()
{
	bool ok;
	if (!player->getNameSetted()) {
		
		demandeUsername->setMinimumSize(1000, 1000);
		QString text = demandeUsername->getText(this, tr("Entrez votre nom"),
			tr("Username:"), QLineEdit::Normal,
			"Enter username", &ok, Qt::MSWindowsFixedSizeDialogHint);

		if (!text.isEmpty() && ok )
		{
			player->setNameSetted(true);
			player->setUsername((text.simplified().remove(' ')).toStdString());
			fenetrePointage->setJoueurUsername();
			fenetrePointage->show();
			this->setEnabled(false);
		}
	}
}

void FenetrePrincipale::closeEvent(QCloseEvent* event)
{
	if (fenetrePointage != nullptr)
	{
		fenetrePointage->hide();
	}
}

