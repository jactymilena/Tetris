#include "BoutonPrincipal.h"

BoutonPrincipal::BoutonPrincipal()
{
	setStyleSheet("QPushButton{font:bold;background: transparent;color:#0ccaf6;font-size: 36px;}");
	setFocusPolicy(Qt::NoFocus);
	setFixedSize(500, 80);
	//setMouseTracking(true);
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
	setStyleSheet("QPushButton{font:bold;background: transparent;color:white;font-size: 36px;}");
}
void BoutonPrincipal::hoverLeave(QHoverEvent* event)
{
	setStyleSheet("QPushButton{font:bold;background: transparent;color:#0ccaf6;font-size: 36px;}");
}
void BoutonPrincipal::hoverMove(QHoverEvent* event)
{

}