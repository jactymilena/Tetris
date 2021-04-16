/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: BoutonPrincipal.cpp
Date: 13 avril 2021
But: Bouton qui change lorsqu'on passe le curseur sur celui-ci
====================================*/

#include "BoutonPrincipal.h"

BoutonPrincipal::BoutonPrincipal()
{
	setStyleSheet("QPushButton{ font:bold;background: transparent;color:#0ccaf6;font-size: 36px;}");
	setFocusPolicy(Qt::NoFocus);
	setFixedSize(500, 80);
}
BoutonPrincipal::~BoutonPrincipal()
{

}

// Rédéfinition de la fonction event qui rédéfinit les évenements qui se produisent lorsque le curseur passe par le curseur
bool BoutonPrincipal::event(QEvent* event)
{
	switch (event->type())
	{
	case QEvent::HoverEnter:
		hoverEnter(static_cast<QHoverEvent*>(event));
		return true;
		break;
	case QEvent::HoverLeave:
		hoverLeave(static_cast<QHoverEvent*>(event));
		return true;
		break;
	}
	return QWidget::event(event);
}

// Change la couleur du bouton lorsque le curseur est mis sur le bouton
void BoutonPrincipal::hoverEnter(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent; color: white; font-size: 36px; border: solid white; border-width: 0px 0px 2px 0px;}");
}

// Change la couleur du bouton lorsque le curseur est enlevé du bouton
void BoutonPrincipal::hoverLeave(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent; color: #0ccaf6; font-size: 36px;}");
}
