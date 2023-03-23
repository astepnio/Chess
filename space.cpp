#include "space.h"

Space::Space() {
	empty = true;
	currentPiece = nullptr;
}

void Space::setPiece(int x, int y, int color) {
	empty = false;
	if (x == 1 || x == 6 ) { // second row, all pawns
		currentPiece = new Pawn(x, y, color);
	}
	else if (x == 0 || x == 7) { //first or last row
		if (y == 0 || y == 7 ) { //rook
			currentPiece = new Rook(x, y, color);
		}
		else if (y == 1 || y == 6) { //knight
			currentPiece = new Knight(x, y, color);
		}
		else if (y == 2 || y == 5 ) { //bishop
			currentPiece = new Bishop(x, y, color);
		}
		else if (y == 3) { //queen
			currentPiece = new Queen(x, y, color);
		}
		else if (y == 4) { //king
			currentPiece = new King(x, y, color);
		}
	}
	else { //empty space
		currentPiece = nullptr;
		empty = true;
	}
}

bool Space::movePiece(Space* target) {
	bool valid{ false };
	if (currentPiece != nullptr) { //if not empty
		if (currentPiece->move(target) ) { //if successfully moved
			valid = true;
		}
	}

	return valid;
}

void Space::setPiece(Piece* piece) {
	currentPiece = piece;
 }
