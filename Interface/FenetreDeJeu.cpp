#include "FenetreDeJeu.h"

FenetreDeJeu::FenetreDeJeu(): QWidget(),
	labelDeJeu(nullptr),
	layout(nullptr)
{
	labelDeJeu = new QLabel("label");
	labelDeJeu2 = new QLabel("label");

	layout = new QHBoxLayout();
	layout->addWidget(labelDeJeu);
	
	boardInit();
	layout->addWidget(labelDeJeu2);
	setLayout(layout);
	
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