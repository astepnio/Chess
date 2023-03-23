#pragma once

#include "chess.h"
#include "space.h"
#include "piece.h"

class Chessboard {

private:
	std::array < char , 8 > letterPositions = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
	Space* selectedSpace; //pointer to currently selected space
	int turn{}; //tracks total moves made
	int currentColorsTurn{ white };  //white == 1, black == 0
	
public:
	//constructors
	Chessboard();

	//methods
	void print();
	void generate();
	bool printHelp();
	void clearInputBuffer();
	void displayCurrentTurn();
	
	Space* getUserSelectedSpace();

	static Space** grid; //2d array of Space objects which contain pointers to our piece objects
};
