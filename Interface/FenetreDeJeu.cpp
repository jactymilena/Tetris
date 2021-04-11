#include "FenetreDeJeu.h"

FenetreDeJeu::FenetreDeJeu(): QWidget(),
	labelDeJeu(nullptr),
	layout(nullptr)
{
	labelDeJeu = new QLabel("label");
	labelDeJeu2 = new QLabel("label");
	labelDeJeu->setFocusPolicy(Qt::NoFocus);
	labelDeJeu2->setFocusPolicy(Qt::NoFocus);

	layout = new QHBoxLayout();
	layout->addWidget(labelDeJeu);
	
	boardInit();
	layout->addWidget(labelDeJeu2);
	setLayout(layout);
	//resize(550, 370);
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