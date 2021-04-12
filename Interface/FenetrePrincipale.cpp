#include "FenetrePrincipale.h"
#include <QDir>

FenetrePrincipale::FenetrePrincipale():boutonPourFenetreJeu(nullptr),
boutonPourFenetreReglage(nullptr),
boutonPourScore(nullptr),
labelTetris(nullptr),
layoutVertical1(nullptr),
widget(nullptr),
fenetreDeJeu(nullptr),
fenetrePointage(nullptr),
demandeUsername(nullptr)
{
	
	labelTetris = new QLabel();
	labelTetris->setText("QTETRIS MANIA");
	QFont font = labelTetris->font();
	font.setPointSize(40);
	labelTetris->setFont(font);
	boutonPourFenetreJeu = new QPushButton("Nouvelle Partie");
	boutonPourFenetreReglage = new QPushButton("Reglages");
	boutonPourScore = new QPushButton("Pointage");
	
	layoutVertical1 = new QVBoxLayout();
	widget = new QWidget();

	layoutVertical1->addWidget(labelTetris);
	layoutVertical1->setAlignment(labelTetris, Qt::AlignCenter);
	layoutVertical1->addWidget(boutonPourFenetreJeu);
	layoutVertical1->addWidget(boutonPourFenetreReglage);
	layoutVertical1->addWidget(boutonPourScore);

	widget->setLayout(layoutVertical1);

	setCentralWidget(widget);
	fenetrePointage = new FenetrePointage(this);
	demandeUsername = new QInputDialog();


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