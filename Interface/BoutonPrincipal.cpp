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

void BoutonPrincipal::hoverEnter(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent; color: white; font-size: 36px; border: solid white; border-width: 0px 0px 2px 0px;}");
}

void BoutonPrincipal::hoverLeave(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent; color: #0ccaf6; font-size: 36px;}");
}
