#include "FenetrePrincipale.h"

FenetrePrincipale::FenetrePrincipale():boutonPourFenetreJeu(nullptr),
boutonPourFenetreReglage(nullptr),
boutonPourScore(nullptr),
labelTetris(nullptr),
layoutVertical1(nullptr),
widget(nullptr),
fenetreDeJeu(nullptr)
{
	labelTetris = new QLabel();
	labelTetris->setText("QTETRIS MANIA");
	QFont font = labelTetris->font();
	font.setPointSize(40);
	labelTetris->setFont(font);
	boutonPourFenetreJeu = new QPushButton("Nouvelle Partie");
	boutonPourFenetreJeu->setFocusPolicy(Qt::NoFocus);
	boutonPourFenetreReglage = new QPushButton("Reglages");
	boutonPourFenetreReglage->setFocusPolicy(Qt::NoFocus);
	boutonPourScore = new QPushButton("Pointage");
	boutonPourScore->setFocusPolicy(Qt::NoFocus);
	
	layoutVertical1 = new QVBoxLayout();
	widget = new QWidget();

	layoutVertical1->addWidget(labelTetris);
	layoutVertical1->setAlignment(labelTetris, Qt::AlignCenter);
	layoutVertical1->addWidget(boutonPourFenetreJeu);
	layoutVertical1->addWidget(boutonPourFenetreReglage);
	layoutVertical1->addWidget(boutonPourScore);

	widget->setLayout(layoutVertical1);

	setCentralWidget(widget);

	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetreDeJeu()));
}

FenetrePrincipale::~FenetrePrincipale()
{
}

void FenetrePrincipale::slotPourFenetreDeJeu()
{
	fenetreDeJeu = new FenetreDeJeu;
	setCentralWidget(fenetreDeJeu);
}