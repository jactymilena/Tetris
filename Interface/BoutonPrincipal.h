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

