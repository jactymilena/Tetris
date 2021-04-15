/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: BoutonPrincipal.cpp
Date: 15 avril 2021
But: Bouton qui change lorsqu'on passe le curseur sur celui-ci
====================================*/
#include "BoutonPrincipal.h"

BoutonPrincipal::BoutonPrincipal()
{
	setStyleSheet("QPushButton{font:bold;background: transparent;color:#0ccaf6;font-size: 36px;}");
	setFocusPolicy(Qt::NoFocus);
	setFixedSize(500, 80);
}
BoutonPrincipal::~BoutonPrincipal()
{

}

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
	case QEvent::HoverMove:
		hoverMove(static_cast<QHoverEvent*>(event));
		return true;
		break;
	default:
		break;
	}
	return QWidget::event(event);
}
void BoutonPrincipal::hoverEnter(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent; color: white; font-size: 36px;}");
}
void BoutonPrincipal::hoverLeave(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent; color: #0ccaf6; font-size: 36px;}");
}
void BoutonPrincipal::hoverMove(QHoverEvent* event)
{

}