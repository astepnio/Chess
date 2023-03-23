#pragma once

#include "chess.h"
#include "space.h"
class Space;

enum colors {
	black,
	white,
	none
};

enum id {
	pawn, //0
	rook,
	knight,
	bishop,
	queen,
	king //5
};

class Piece {
protected: 
	//coordinates on grid
	int x;
	int y;

	int id;
	int totalMoves;
	int value;
	int color;
	char symbol;
	std::string pieceType; 
public:
	Piece(int value, int x, int y, int color); 

	
	char getSymbol() { return symbol; };
	int getId() { return id; };
	int getColor() { return color; };
	int getXpos() { return x; };
	int getYpos() { return y; };
	int getValue() { return value; };
	std::string getPieceType() { return pieceType; };
	int getTotalMoves() { return totalMoves; };


	virtual bool move(Space*);

	void increaeTotalMoves() { ++totalMoves; }; //increment by 1

};

class Pawn : public Piece {
private:
	
public:
	Pawn(int, int, int);
	bool move(Space*);
};

class Rook : public Piece {
private:
	
public:
	Rook(int, int, int);
	bool move(Space*);
};

class Knight : public Piece {
private:

public:
	Knight(int, int, int);
	bool move(Space*);
};

class Bishop : public Piece {
private:

public:
	Bishop(int, int, int);
	bool move(Space*);
};

class Queen : public Piece {
private:

public:
	Queen(int, int, int);
	bool move(Space*);
};

class King : public Piece {
private:
	
public:
	King(int, int, int);
	bool move(Space*);
};

