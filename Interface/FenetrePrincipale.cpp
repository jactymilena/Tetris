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
	boutonPourFenetreJeu = new BoutonPrincipal();
	boutonPourFenetreJeu->setText("Nouvelle Partie");
	boutonPourFenetreReglage = new BoutonPrincipal();
	boutonPourFenetreReglage->setText("Reglages");
	boutonPourScore = new BoutonPrincipal();
	boutonPourScore->setText("Pointage");

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
	//demandeUsername->setOption(QInputDialog::);
	demandeUsername->setWindowTitle("Votre nom");
	demandeUsername->setWindowIcon(iconeHautPage);
	demandeUsername->setLabelText("Entrez votre nom:");
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
	layoutVertical1->addWidget(boutonPourFenetreReglage);
	layoutVertical1->setAlignment(boutonPourFenetreReglage, Qt::AlignHCenter);
	layoutVertical1->addWidget(boutonPourScore);
	layoutVertical1->setAlignment(boutonPourScore, Qt::AlignHCenter);

	//Ajout widget au layout
	widget->setLayout(layoutVertical1);
	setFixedSize(900, 750);
	setCentralWidget(widget);
	QObject::connect(boutonPourScore, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetrePointage()));
	fenetreDeJeu = new FenetreDeJeu(this, player);
	fenetreAide = new FenetreAide(this);
	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), SLOT(slotPourFenetreDeJeu()));
	QObject::connect(boutonPourFenetreReglage, SIGNAL(clicked(bool)), SLOT(slotChangerFenetreAide()));
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
	//MCIERROR error = mciSendString(L"setaudio maintheme volume to 600", nullptr, 0, nullptr);
	//MCIERROR error = mciSendStringA("set maintheme speed 1100", nullptr, 0, 0);
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

void FenetrePrincipale::closeEvent(QCloseEvent* event)
{
	if (fenetrePointage != nullptr)
	{
		fenetrePointage->hide();
	}
	mciSendStringA("close Tetris.mp3" , nullptr, 0, nullptr);
}

