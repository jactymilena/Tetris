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

	//qDebug() << "FenetreDeJeu " << this->hasFocus();
}

//void FenetreDeJeu::keyPressEvent(QKeyEvent* event) {
//	qDebug() << "jeu key event";
//}

void FenetreDeJeu::boardInit() {
	board = new Board();
	board->setFocus();
	board->setFocusPolicy(Qt::StrongFocus);
	layout->addWidget(board);
}

FenetreDeJeu::~FenetreDeJeu()
{
	close();
	delete labelDeJeu;
	delete layout;
}