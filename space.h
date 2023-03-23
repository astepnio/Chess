#pragma once

#include "chess.h";
#include "piece.h";
class Piece;

class Space {
private:
	bool empty;
	Piece* currentPiece;
	int x;
	int y;

public:
	Space();

	Piece* getPiece() { return currentPiece; };
	void setPiece(int, int, int); // value, x, y, color
	void setPiece(Piece*); //pointer to piece object
	bool isEmpty() { return empty; };

	bool movePiece(Space*);
	

	int getX() { return x; };
	int getY() { return y; };

	void setX(int xCoordinate) { x = xCoordinate; };
	void setY(int yCoordinate) { y = yCoordinate; };
};
