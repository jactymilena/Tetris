#include "FramePourPiece.h"

FramePourPiece::FramePourPiece(Piece laPiece)
{
	pieceAMontrer = laPiece;
	setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
	setLineWidth(2);
	setMidLineWidth(3);
	//setStyleSheet("background-color: rgb(0, 0, 0);");
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