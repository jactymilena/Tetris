#pragma once
#include <QFrame>
#include <QPainter>
#include "Piece.h"
class FramePourPiece : public QFrame
{
public:
	FramePourPiece(Piece laPiece);
	~FramePourPiece();

	void setPiece(Piece pieceRefresh);
protected:
	void paintEvent(QPaintEvent* event);

private:
	Piece pieceAMontrer;
};

