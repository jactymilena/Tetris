#include "FenetreDeJeu.h"

FenetreDeJeu::FenetreDeJeu():labelDeJeu(nullptr),
layoutVerticalFenetreDeJeu(nullptr)
{
	labelDeJeu = new QLabel("label");
	layoutVerticalFenetreDeJeu = new QVBoxLayout();
	layoutVerticalFenetreDeJeu->addWidget(labelDeJeu);

	setLayout(layoutVerticalFenetreDeJeu);
	
}
FenetreDeJeu::~FenetreDeJeu()
{
	close();
	delete labelDeJeu;
	delete layoutVerticalFenetreDeJeu;
}