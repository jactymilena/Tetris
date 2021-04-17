#pragma once
/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: FenetreAide.cpp
Date: 15 avril 2021
But: Fenetre avec tous les paramètres:sons et commandes
====================================*/

#include "FenetreAide.h"
#include "FenetreDeJeu.h"

FenetreAide::FenetreAide(QMainWindow* fenetrePrincipale) :
	m_layoutAide(nullptr), m_layoutGrid(nullptr),m_layoutBob(nullptr),m_layoutGridSon(nullptr), m_label1(nullptr), m_label2(nullptr), 
	m_label3(nullptr), m_label4(nullptr), m_label5(nullptr),m_label6(nullptr), m_label7(nullptr), m_labelson(nullptr), m_labelsfx(nullptr),
	m_touche1(nullptr), m_touche2(nullptr), m_touche3(nullptr),m_touche4(nullptr), m_touche5(nullptr), m_touche6(nullptr), m_touche7(nullptr),
	boutonPourFenetreRetour(nullptr), m_sons(nullptr),m_sfx(nullptr)

{
	valeur = 5;
	volume = 500;
	//Création des layout
	m_layoutAide = new QVBoxLayout();
	m_layoutGrid = new QGridLayout();
	m_layoutBob = new QVBoxLayout();
	m_layoutGridSon = new QGridLayout();

	//Création des GroupBox
	m_group1 = new QGroupBox();
	m_group2 = new QGroupBox();
	m_group3 = new QGroupBox();

	//Création des Labels 
	m_label1 = new QLabel();
	m_label2 = new QLabel();
	m_label3 = new QLabel();
	m_label4 = new QLabel();
	m_label5 = new QLabel();
	m_label6 = new QLabel();
	m_label7 = new QLabel();
	m_labelson = new QLabel();
	m_labelsfx = new QLabel();

	//Création des LineEdit
	m_touche1 = new QLineEdit();	
	m_touche2 = new QLineEdit(); 
	m_touche3 = new QLineEdit();
	m_touche4 = new QLineEdit();
	m_touche5 = new QLineEdit();
	m_touche6 = new QLineEdit();
	m_touche7 = new QLineEdit();

	//Création du bouton de retour
	boutonPourFenetreRetour = new BoutonPrincipal();

	//Création des bars de sons
	m_sons = new QSlider(Qt::Horizontal);
	m_sons->setMinimum(0);
	m_sons->setMaximum(10);
	m_sons->setValue(5);
	m_sons->setPageStep(1);
	m_sfx = new QSlider(Qt::Horizontal);
	m_sfx->setMinimum(0);
	m_sfx->setMaximum(10);
	m_sfx->setValue(5);
	m_sfx->setPageStep(1);
	
	
	//Attribution d'un style et de texte 
	m_sons->setStyleSheet("background : transparent; color: white;");
	m_sfx->setStyleSheet("background : transparent; color: white;");
	m_label1->setText("MOVE RIGHT");
	m_label1->setStyleSheet("background : transparent; color: white;");
	m_label2->setText("MOVE LEFT");
	m_label2->setStyleSheet("background : transparent; color: white;");
	m_label3->setText("ROTATE RIGHT");
	m_label3->setStyleSheet("background : transparent; color: white;");
	m_label4->setText("ROTATE LEFT");
	m_label4->setStyleSheet("background : transparent; color: white;");
	m_label5->setText("HOLD");
	m_label5->setStyleSheet("background : transparent; color: white;");
	m_label6->setText("HARD DROP");
	m_label6->setStyleSheet("background : transparent; color: white;");
	m_label7->setText("Have fun or die trying ;)");
	m_label7->setStyleSheet("background : transparent; color: white; font-size:32px");
	m_label7->setFont(QFont("Century Gothic"));
	m_label7->setAlignment(Qt::AlignCenter);
	m_labelsfx->setText("SFX SOUND");
	m_labelsfx->setStyleSheet("background : transparent; color: white;");
	m_labelson->setText("MUSIC");
	m_labelson->setStyleSheet("background : transparent; color: white;");

	//Attribution d'un style, d'un texte et d'un état
	m_touche1->setText("RIGHT ARROW");
	m_touche1->setStyleSheet("background : transparent; background-color : rgba(120, 120, 120, 200); color: white;");
	m_touche1->setEnabled(false);
	m_touche2->setText("LEFT ARROW");
	m_touche2->setStyleSheet("background : transparent; background-color : rgba(120, 120, 120, 200); color: white;");
	m_touche2->setEnabled(false);
	m_touche3->setText("E");
	m_touche3->setStyleSheet("background : transparent; background-color : rgba(120, 120, 120, 200); color: white;");
	m_touche3->setEnabled(false);
	m_touche4->setText("Q");
	m_touche4->setStyleSheet("background : transparent; background-color : rgba(120, 120, 120, 200); color: white;");
	m_touche4->setEnabled(false);
	m_touche5->setText("W");
	m_touche5->setStyleSheet("background : transparent; background-color : rgba(120, 120, 120, 200); color: white;");
	m_touche5->setEnabled(false);
	m_touche6->setText("DOWN ARROW");
	m_touche6->setStyleSheet("background : transparent; background-color : rgba(120, 120, 120, 200); color: white;");
	m_touche6->setEnabled(false);

	//Attribution d'un style  
	m_group1->setStyleSheet("QGroupBox { background : transparent; border: none}");
	m_group2->setStyleSheet("QGroupBox { background : transparent; border: none}");
	m_group3->setStyleSheet("QGroupBox { background : transparent; border: none}");

	boutonPourFenetreRetour->setText("BACK");
	
	//Commandes
	m_layoutGrid->addWidget(m_label1, 0, 0, Qt::AlignRight);
	m_layoutGrid->addWidget(m_label2, 1, 0, Qt::AlignRight);
	m_layoutGrid->addWidget(m_label3, 2, 0, Qt::AlignRight);
	m_layoutGrid->addWidget(m_label4, 3, 0, Qt::AlignRight);
	m_layoutGrid->addWidget(m_label5, 4, 0, Qt::AlignRight);
	m_layoutGrid->addWidget(m_label6, 5, 0, Qt::AlignRight);
	m_layoutGrid->addWidget(m_touche1, 0, 1, Qt::AlignLeft);
	m_layoutGrid->addWidget(m_touche2, 1, 1, Qt::AlignLeft);
	m_layoutGrid->addWidget(m_touche3, 2, 1, Qt::AlignLeft);
	m_layoutGrid->addWidget(m_touche4, 3, 1, Qt::AlignLeft);
	m_layoutGrid->addWidget(m_touche5, 4, 1, Qt::AlignLeft);
	m_layoutGrid->addWidget(m_touche6, 5, 1, Qt::AlignLeft);
	
	//Retour 
	m_layoutBob->addWidget(m_label7);
	m_layoutBob->addWidget(boutonPourFenetreRetour);
	m_layoutBob->setAlignment(boutonPourFenetreRetour, Qt::AlignHCenter);

	//Sons
	m_layoutGridSon->addWidget(m_labelson);
	m_layoutGridSon->addWidget(m_sons);
	m_layoutGridSon->addWidget(m_labelsfx);
	m_layoutGridSon->addWidget(m_sfx);

	//Attribution des Layout au GroupBox
	m_group1->setLayout(m_layoutGrid);
	m_group3->setLayout(m_layoutGridSon);
	m_group2->setLayout(m_layoutBob);

	//Attribution au Layout principale
	m_layoutAide->addWidget(m_group1);
	m_layoutAide->addWidget(m_group3);
	m_layoutAide->addWidget(m_group2);

	//Activer le layout
	setLayout(m_layoutAide);
	
	//Actions possibles
	QObject::connect(boutonPourFenetreRetour, SIGNAL(clicked(bool)), this, SLOT(slotPourFenetreRetour()));
	QObject::connect(this, SIGNAL(retourFenetreAvant()), fenetrePrincipale, SLOT(slotChangerFenetrePrincipale()));
	QObject::connect(m_sons, SIGNAL(valueChanged(int)), this, SLOT(slotSon()));

	
}


void FenetreAide::slotSon()
{
	if(m_sons->value() > valeur)
	{
		volume += 100;
		valeur = m_sons->value();
		std::string string1 = "setaudio maintheme volume to " + std::to_string(volume);
		std::wstring wstring1 = std::wstring(string1.begin(), string1.end());
		const wchar_t* wchar1 = wstring1.c_str();
		mciSendString(wchar1,0,0,0);
	}
	if (m_sons->value() < valeur)
	{
		volume -= 100;
		valeur = m_sons->value();
		std::string string1 = "setaudio maintheme volume to " + std::to_string(volume);
		std::wstring wstring1 = std::wstring(string1.begin(), string1.end());
		const wchar_t* wchar1 = wstring1.c_str();
		mciSendString(wchar1, 0, 0, 0);
	}
}

void FenetreAide::slotSFX()
{

}

FenetreAide::~FenetreAide()
{
	close();
}

void FenetreAide::slotPourFenetreRetour()
{
	emit retourFenetreAvant();
}