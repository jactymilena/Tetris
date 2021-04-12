#pragma once
#include "FenetreAide.h"


FenetreAide::FenetreAide(QMainWindow* fenetrePrincipale) :
	m_layoutAide(nullptr)

{
	m_layoutAide = new QVBoxLayout();





}

FenetreAide::~FenetreAide()
{
	close();
}