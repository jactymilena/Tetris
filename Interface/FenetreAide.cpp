#pragma once
#include "FenetreAide.h"


FenetreAide::FenetreAide(QMainWindow* fenetrePrincipale) :
	m_layoutAide(nullptr), label1(nullptr),label2(nullptr),label3(nullptr),label4(nullptr)

{
	m_layoutAide = new QVBoxLayout();
	label1 = new QLabel();
	label1->setText("Tourner -> ");
	label2 = new QLabel();	
	label2->setText("Gauche -> ");
	label3 = new QLabel();
	label3->setText("Droite -> ");
	label4 = new QLabel();
	label4->setText("Descendre -> ");

	m_layoutAide->addWidget(label1);
	m_layoutAide->addWidget(label2);
	m_layoutAide->addWidget(label3);
	m_layoutAide->addWidget(label4);

	setLayout(m_layoutAide);



}

FenetreAide::~FenetreAide()
{
	close();
}