#include "FenetreDeJeu.h"

FenetreDeJeu::FenetreDeJeu():labelDeJeu(nullptr),
layoutVerticalFenetreDeJeu(nullptr), menuBar(nullptr), menu(nullptr){
	menuBar = new QMenuBar();
	menu = new QMenu("Menu");
	menuBar->addMenu(menu);
	labelDeJeu = new QLabel("label");
	layoutVerticalFenetreDeJeu = new QVBoxLayout();
	layoutVerticalFenetreDeJeu->addWidget(labelDeJeu);

	layoutVerticalFenetreDeJeu->setMenuBar(menuBar);
	setLayout(layoutVerticalFenetreDeJeu);
	
}
FenetreDeJeu::~FenetreDeJeu()
{
	close();
	delete labelDeJeu;
	delete layoutVerticalFenetreDeJeu;
}