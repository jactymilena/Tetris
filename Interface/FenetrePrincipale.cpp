#include "FenetrePrincipale.h"
#include <QDir>

FenetrePrincipale::FenetrePrincipale():
boutonPourFenetreJeu(nullptr),
boutonPourFenetreReglage(nullptr),
boutonPourScore(nullptr),
labelTetris(nullptr),
layoutVertical1(nullptr),
widget(nullptr),
fenetreDeJeu(nullptr),
index(nullptr),
fenetrePointage(nullptr),
demandeUsername(nullptr)
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
	fenetrePointage = new FenetrePointage(this);
	demandeUsername = new QInputDialog();

	//Action
	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), SLOT(slotPourFenetreDeJeu()));
	index->addWidget(widget);
	index->addWidget(fenetreDeJeu);
	setCentralWidget(index);
	index->setCurrentIndex(0);
	QObject::connect(boutonPourFenetreJeu, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetreDeJeu()));
	QObject::connect(boutonPourScore, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetrePointage()));
	
}

FenetrePrincipale::~FenetrePrincipale()
{
	
}

void FenetrePrincipale::slotPourFenetreDeJeu()
{
	fenetreDeJeu = new FenetreDeJeu;
	setCentralWidget(fenetreDeJeu);
}

void FenetrePrincipale::slotPourFenetrePointage()
{
	bool ok;
	demandeUsername->setMinimumSize(1000, 1000);	
	QString text = demandeUsername->getText(this, tr("Entrez votre nom"),
		tr("Username:"), QLineEdit::Normal,
		QDir::home().dirName(), &ok, Qt::MSWindowsFixedSizeDialogHint);
	
	if (ok && !text.isEmpty())
	{
		fenetrePointage->setJoueurUsername(text.toStdString());
			this->setEnabled(false);
		fenetrePointage->show();
	}
	

}

void FenetrePrincipale::closeEvent(QCloseEvent* event)
{
	if(fenetrePointage != nullptr)
	{
		fenetrePointage->hide();
	}
}

void FenetrePrincipale::slotPourEnableFenetre()
{
	this->setEnabled(true);
}

	index->setCurrentIndex(1);
}

void FenetrePrincipale::slotChangerFenetrePrincipale()
{
	index->setCurrentIndex(0);
}