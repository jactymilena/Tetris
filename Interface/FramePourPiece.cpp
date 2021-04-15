/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: FramePourPiece.cpp
Date:           15 avril 2021
But:            Montre la pièce dans une boîte notamment pour les pièces en Hold
====================================*/

#include "FramePourPiece.h"

FramePourPiece::FramePourPiece(Piece laPiece)
{
	pieceAMontrer = laPiece;
	setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
	setLineWidth(2);
	setMidLineWidth(3);
	setStyleSheet("background : transparent; border: 2px solid white");
	setFixedSize(250, 250);
	activateWindow();
}

FramePourPiece::~FramePourPiece()
{

}

void FramePourPiece::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QPainter painter2(this);
	painter2.setPen(QPen(Qt::white));
	QRect rect = contentsRect();
	float largeurCarre = contentsRect().width() / 6.0;
	float hauteurCarre = contentsRect().height() / 6.0;;

	if (pieceAMontrer.getNumPiece() != 7)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 2; j < 6; j++) {
				for (int z = 0; z < 4; z++)
				{

					if (pieceAMontrer.getCarre(z).ligne == i && pieceAMontrer.getCarre(z).colonne == j)
					{
						painter2.setBrush(QBrush(colorTab[pieceAMontrer.getNumColor()]));
						painter2.drawRect(QRect((j-1) * largeurCarre + rect.topLeft().x(), (i+2) * hauteurCarre + rect.topLeft().y(), largeurCarre, hauteurCarre));
					}
				}
			}
		}
	}
}

void FramePourPiece::setPiece(Piece pieceRefresh)
{
	pieceAMontrer = pieceRefresh;
	repaint();
}