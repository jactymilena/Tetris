#pragma once
#include "FenetreAide.h"


FenetreAide::FenetreAide(QMainWindow* fenetrePrincipale) :
	m_layoutAide(nullptr), m_label1(nullptr), m_label2(nullptr), m_label3(nullptr), m_label4(nullptr), m_label5(nullptr),m_label6(nullptr)

{
	m_layoutAide = new QVBoxLayout();
	m_label1 = new QLabel();
	m_label2 = new QLabel();
	m_label3 = new QLabel();
	m_label4 = new QLabel();
	m_label5 = new QLabel();
	m_label6 = new QLabel();
	
	m_label1->setText("Tourner -> ");
	m_label2->setText("Gauche -> ");
	m_label3->setText("Droite -> ");
	m_label4->setText("Descendre -> ");
	m_label5->setText("Garder ->");
	m_label6->setText("Have fun or die trying ;)");
	m_layoutAide->addWidget(label1);
	m_layoutAide->addWidget(label2);
	m_layoutAide->addWidget(label3);
	m_layoutAide->addWidget(label4);

	m_layoutAide->addWidget(m_label1);
	m_layoutAide->addWidget(m_label2);
	m_layoutAide->addWidget(m_label3);
	m_layoutAide->addWidget(m_label4);
	m_layoutAide->addWidget(m_label5);
	m_layoutAide->addWidget(m_label6);

	setLayout(m_layoutAide);


}

FenetreAide::~FenetreAide()
{
	close();
}