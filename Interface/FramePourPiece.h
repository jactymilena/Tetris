#pragma once
/*===================================
Auteur:         fona1101 elka0602 saej3101
Nom du fichier: FramePourPiece.h
Date:           15 avril 2021
But:            Déclarer FramePourPiece.h
====================================*/

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

