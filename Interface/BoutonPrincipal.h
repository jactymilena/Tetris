/*===================================
Auteur: fona1101 elka0602 saej3101
Nom du fichier: BoutonPrincipal.h
Date: 15 avril 2021
But: Déclarer BoutonPrincipal.h
====================================*/
#pragma once
#include <QPushButton>
#include <QHoverEvent>
#include <QEvent>
#include <qdebug.h>
class BoutonPrincipal : public QPushButton
{
	
public:
	BoutonPrincipal();
	~BoutonPrincipal();
protected:
	void hoverEnter(QHoverEvent* event);
	void hoverLeave(QHoverEvent* event);
	void hoverMove(QHoverEvent* event);
	bool event(QEvent* event);
};

