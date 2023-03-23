#include "piece.h"
#include "chessboard.h"
constexpr int gridSize{ 8 }; //size of grid for calculations

Piece::Piece(int value, int x, int y, int color) {
	id = 0;
	totalMoves = 0;
	this->value = value;
	this->color = color;
	this-> x=x;
	this->y=y;
}

Pawn::Pawn(int x, int y, int color) : Piece(1, x, y, color) { // Piece(value)
	this->id = pawn;
	this->symbol = 'p';
	this->pieceType = "Pawn";

}

Rook::Rook(int x, int y, int color) : Piece(5, x, y, color) {
	this->id = rook;
	this->symbol = 'r';
	this->pieceType = "Rook";
}

Knight::Knight(int x, int y, int color) : Piece(3, x, y, color) {
	this->id = knight;
	this->symbol = 'h';
	this->pieceType = "Knight";
}

Bishop::Bishop(int x, int y, int color) : Piece(3, x, y, color) {
	this->id = bishop;
	this->symbol = 'b';
	this->pieceType = "Bishop";
}

Queen::Queen(int x, int y, int color) : Piece(9, x, y, color) {
	this->id = queen;
	this->symbol = 'q';
	this->pieceType = "Queen";
}

King::King(int x, int y, int color) : Piece(0, x, y, color) {
	this->id = king;
	this->symbol = 'k';
	this->pieceType = "King";
}

bool Piece::move(Space* selectedSpace) { //placeholder for virtual function
	return false;
}

bool Pawn::move(Space* selectedSpace) {
	bool valid{ false };
	if (totalMoves == 0) { //if first move
		if (selectedSpace->getPiece() == nullptr) { //if empty space
			if (selectedSpace->getY() == y) { //if aligned vertically
				if (selectedSpace->getX() == x + 1 || selectedSpace->getX() == x + 2) { valid = true; }
				if (selectedSpace->getX() == x - 1 || selectedSpace->getX() == x - 2) { valid = true; }
			}
		}
		else if(selectedSpace->getPiece() != nullptr){ //if space is not empty
			if (!selectedSpace->getY() == y + 1 || selectedSpace->getY() == y - 1) { //if not aligned vertically
				if (selectedSpace->getX() == x + 1 || selectedSpace->getX() == x + 2) { valid = true; }
				else if (selectedSpace->getX() == x - 1 || selectedSpace->getY() == x - 2) { valid = true; }
			}
		}
	}
	else { //if not first move
		if (selectedSpace->getPiece() == nullptr) { //if empty
			if (selectedSpace->getY() == y) { //if aligned vertically
				if (selectedSpace->getX() == x + 1) { valid = true; }
			}
		}
		else { //if space is not empty
			if (selectedSpace->getY() == y + 1 || selectedSpace->getY() == y - 1) {
				if (selectedSpace->getX() == x + 1 ){ valid = true; }
			}
		}
	}
	return valid;
}

bool Rook::move(Space* selectedSpace) {
	int numObstacles{ 0 };
	bool valid{ false };
	
	if (selectedSpace->getY() == y) { //vertical movement
		if (selectedSpace->getX() < x) { //upwards movement
			for (int i = (x - 1); i >= selectedSpace->getX(); --i) { //each tile in the row
				if (Chessboard::grid[i][y].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles == 1 && selectedSpace->getPiece() != nullptr && selectedSpace->getPiece()->getColor() != color) { valid = true; }
			else if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
		else if(selectedSpace->getX() > x) { //downwards movement
			for (int i = (x + 1); i <= selectedSpace->getX(); ++i) { //each tile in the rowi
				if (Chessboard::grid[i][y].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles == 1 && selectedSpace->getPiece() != nullptr && selectedSpace->getPiece()->getColor() != color) { valid = true; }
			else if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
	}
	else if (selectedSpace->getX() == x) { //horizontal movement
		if (selectedSpace->getY() < y) { //leftwards movement
			for (int i = (y - 1); i >= selectedSpace->getY(); --i) {
				if (Chessboard::grid[x][i].getPiece() != nullptr) { ++numObstacles;	}
			}
			if (numObstacles == 1 && selectedSpace->getPiece() != nullptr && selectedSpace->getPiece()->getColor() != color) { valid = true; }
			else if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
		else if(selectedSpace->getY() > y ){ //rightwards movement
			for (int i = (y + 1); i <= selectedSpace->getY(); ++i) {
				if (Chessboard::grid[x][i].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles == 1 && selectedSpace->getPiece() != nullptr && selectedSpace->getPiece()->getColor() != color) { valid = true; }
			else if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
		
	}
	return valid;
}

bool Knight::move(Space* selectedSpace) {
	bool valid{ false };
	if (selectedSpace->getY() == y + 1 || selectedSpace->getY() == y -1) { //straight L
		if (selectedSpace->getX() == x + 2 || selectedSpace->getX() == x - 2) {
			if (selectedSpace->getPiece() == nullptr || selectedSpace->getPiece()->getColor() != color) {
				valid = true;
			}
		}
	}
	else if (selectedSpace->getY() == y + 2 || selectedSpace->getY() == y - 2) { //sideways L
		if (selectedSpace->getX() == x + 1 || selectedSpace->getX() == x - 1) {
			if (selectedSpace->getPiece() == nullptr || selectedSpace->getPiece()->getColor() != color) {
				valid = true;
			}
		}
	}
	return valid;
}

bool Bishop::move(Space* selectedSpace) {
	bool valid{ false };
	int numObstacles{ 0 };
	bool complete{ false };
	int hor{ 0 };
	int iterations{ 0 };
	if (selectedSpace->getX() < x) { //up
		if (selectedSpace->getY() > y) { //right
			for (int i = x; i > 0; --i) {
				++iterations;
				hor = y + iterations;
				if (hor >= gridSize) { complete = true; }
				else {
					if (Chessboard::grid[x - iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
			if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			} 
			else if(numObstacles > 0) {
				valid = false;
			}
		}
		else if (selectedSpace->getY() < y) { //left
			for (int i = x; i > 0; --i) {
				++iterations;
				hor = y - iterations;
				if (hor <= 0) { complete = true; }
				else {
					if (Chessboard::grid[x - iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
	} 
	else if (selectedSpace->getX() > x) { //down
		if (selectedSpace->getY() > y) { //right
			for (int i = x; i < gridSize; ++i) {
				++iterations;
				hor = y + iterations;
				if (hor >= gridSize) { complete = true; }
				else {
					if (Chessboard::grid[x + iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
		else if (selectedSpace->getY() < y) { //left
			for (int i = x; i < gridSize; ++i) {
				++iterations;
				hor = y - iterations;
				if (hor <= 0) { complete = true; }
				else {
					if (Chessboard::grid[x + iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
	}
	return valid;
}

bool Queen::move(Space* selectedSpace) {
	bool valid{ false };
	int numObstacles{ 0 };
	bool complete{ false };
	int hor{ 0 };
	int iterations{ 0 };

	if (selectedSpace->getY() == y) { //vertical movement  //STRAIGHT MOVEMENT
		if (selectedSpace->getX() < x) { //upwards movement
			for (int i = (x - 1); i >= selectedSpace->getX(); --i) { //each tile in the row
				if (Chessboard::grid[i][y].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
		else if (selectedSpace->getX() > x) { //downwards movement
			for (int i = (x + 1); i <= selectedSpace->getX(); ++i) { //each tile in the row
				if (Chessboard::grid[i][y].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
	}
	else if (selectedSpace->getX() == x) { //horizontal movement
		if (selectedSpace->getY() < y) { //leftwards movement
			for (int i = (y - 1); i >= selectedSpace->getY(); --i) {
				if (Chessboard::grid[x][i].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}
		else if (selectedSpace->getY() > y) { //rightwards movement
			for (int i = (y + 1); i <= selectedSpace->getY(); ++i) {
				if (Chessboard::grid[x][i].getPiece() != nullptr) { ++numObstacles; }
			}
			if (numObstacles > 0) { valid = false; }
			else { valid = true; }
		}

	}
	
	else if (selectedSpace->getX() < x) { //up   //DIAG MOVEMENT
		if (selectedSpace->getY() > y) { //right 
			for (int i = x; i > 0; --i) {
				++iterations;
				hor = y + iterations;
				if (hor >= gridSize) { complete = true; }
				else {
					if (Chessboard::grid[x - iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
		else if (selectedSpace->getY() < y) { //left
			for (int i = x; i > 0; --i) {
				++iterations;
				hor = y - iterations;
				if (hor <= 0) { complete = true; }
				else {
					if (Chessboard::grid[x - iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
	}
	else if (selectedSpace->getX() > x) { //down
		if (selectedSpace->getY() > y) { //right
			for (int i = x; i < gridSize; ++i) {
				++iterations;
				hor = y + iterations;
				if (hor >= gridSize) { complete = true; }
				else {
					if (Chessboard::grid[x + iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
		else if (selectedSpace->getY() < y) { //left
			for (int i = x; i < gridSize; ++i) {
				++iterations;
				hor = y - iterations;
				if (hor <= 0) { complete = true; }
				else {
					if (Chessboard::grid[x + iterations][hor].getPiece() != nullptr) {
						++numObstacles;
						valid = false;
					}
					else { valid = true; }
				}
				if (complete) break;
			}
			if (selectedSpace->getPiece() != nullptr && numObstacles == 1) {
				valid = true;
			}
			else if (numObstacles > 0) {
				valid = false;
			}
		}
	}
	return valid;
}

bool King::move(Space* selectedSpace) {
	bool valid{ false };
	if (selectedSpace->getX() == x + 1 || selectedSpace->getX() == x - 1) { //vertical
		if (selectedSpace->getY() == y + 1 || selectedSpace->getY() == y - 1 || selectedSpace->getY() == y) {
			if (selectedSpace->getPiece() == nullptr || selectedSpace->getPiece()->getColor() != color) {
				valid = true;
			}
		}
	}
	else if (selectedSpace->getY() == y + 1 || selectedSpace->getY() == y - 1) { //horizontal
		if (selectedSpace->getX() == x + 1 || selectedSpace->getX() == x - 1 || selectedSpace->getX() == x) {
			if (selectedSpace->getPiece() == nullptr || selectedSpace->getPiece()->getColor() != color) {
				valid = true;
			}
		}
	}
	return valid;
}
