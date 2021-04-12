#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale():
boutonPourFenetreJeu(nullptr),
boutonPourFenetreReglage(nullptr),
boutonPourScore(nullptr),
labelTetris(nullptr),
layoutVertical1(nullptr),
widget(nullptr),
fenetreDeJeu(nullptr),
index(nullptr)


{

	index = new QStackedWidget;
	
	//Le titre Tetris Mania 
	labelTetris = new QLabel();
	labelTetris->setText("QTETRIS MANIA");
	QFont font = labelTetris->font();
	font.setPointSize(40);
	labelTetris->setFont(font);

	//Creation des boutons
	boutonPourFenetreJeu = new QPushButton("Nouvelle Partie");
	boutonPourFenetreJeu->setFocusPolicy(Qt::NoFocus);
	boutonPourFenetreReglage = new QPushButton("Reglages");
	boutonPourFenetreReglage->setFocusPolicy(Qt::NoFocus);
	boutonPourScore = new QPushButton("Pointage");
	boutonPourScore->setFocusPolicy(Qt::NoFocus);
	
	//Creation layout 
	layoutVertical1 = new QVBoxLayout();

	//Creation widget 
	widget = new QWidget();

	//Ajout au layout
	layoutVertical1->addWidget(labelTetris);
	layoutVertical1->setAlignment(labelTetris, Qt::AlignCenter);
	layoutVertical1->addWidget(boutonPourFenetreJeu);
	layoutVertical1->addWidget(boutonPourFenetreReglage);
	layoutVertical1->addWidget(boutonPourScore);

	//Ajout widget au layout
	widget->setLayout(layoutVertical1);
	setCentralWidget(widget);
	

	fenetreDeJeu = new FenetreDeJeu(this);


	//Action
	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), SLOT(slotPourFenetreDeJeu()));
	index->addWidget(widget);
	index->addWidget(fenetreDeJeu);
	setCentralWidget(index);
	index->setCurrentIndex(0);
}

FenetrePrincipale::~FenetrePrincipale()
{
}

void FenetrePrincipale::slotPourFenetreDeJeu()
{

	index->setCurrentIndex(1);
}

void FenetrePrincipale::slotChangerFenetrePrincipale()
{
	index->setCurrentIndex(0);
}