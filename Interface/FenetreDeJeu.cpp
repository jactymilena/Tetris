#include "FenetreDeJeu.h"

FenetreDeJeu::FenetreDeJeu(): QWidget(),
	labelDeJeu(nullptr),
	labelDeJeu2(nullptr),
	layout(nullptr)
{
	layout = new QHBoxLayout();

	labelDeJeu = new QLabel("label");
	labelDeJeu2 = new QLabel("label");
	layout->addWidget(labelDeJeu);
	boardInit();
	layout->addWidget(labelDeJeu2);
	setLayout(layout);

	qDebug() << "FenetreDeJeu " << this->hasFocus();
}

void FenetreDeJeu::boardInit() {
	board = new Board();
	layout->addWidget(board);
}

FenetreDeJeu::~FenetreDeJeu()
{
	close();
	delete labelDeJeu;
	delete layout;
}