#include "chessboard.h"

Space** Chessboard::grid;

Chessboard::Chessboard() {
	generate(); //generate fresh board

	print(); //display the board
	Sleep(1000);


	selectedSpace = nullptr;
	bool gameOver{ !printHelp() }; //display help directory
	turn = -1; 
	

	while (!gameOver ) { //gameloop
		++turn; 
		std::string currentColor;
		if (turn % 2 == 0) {
			currentColorsTurn = white;
		    currentColor = "white"; 
		}
		else {
			currentColorsTurn = black;
			currentColor = "black";
		}

		bool moved{ false };
		while (!moved) {
			bool validSelection{ false };
			while (!validSelection) {
				displayCurrentTurn();
				Sleep(500);

				selectedSpace = getUserSelectedSpace(); //get selected space from user

				if (selectedSpace->isEmpty()) { //if the space is empty
					std::cout << "\n\n[Invalid Selection] Space is empty!";
					Sleep(2000);
					system("cls");
					print();
				}
				else if (selectedSpace->getPiece()->getColor() != currentColorsTurn) { //if selected piece is the wrong color
					std::cout << "\n\n[Invalid Selection] That's not your piece!";
					Sleep(2000);
					system("cls");
					print();
				}
				else {
					std::cout << "\n\n [type] " << selectedSpace->getPiece()->getPieceType();
					std::cout << "\n [color] " << currentColor;
					std::cout << "\n [value] " << selectedSpace->getPiece()->getValue() << "\n\n";
					std::cout << "\n [space x:y]" << selectedSpace->getX() << " " << selectedSpace->getY();
					std::cout << "\n [piece x:y]" << selectedSpace->getPiece()->getXpos() << " " << selectedSpace->getPiece()->getYpos();
					validSelection = true;

				}

			}

			//get space or coordinates to move to from user
			validSelection = false;
			Sleep(500);

			std::cout << "\n\n[enter the target coordinates]\n";

			Space* targetDestination = getUserSelectedSpace();
			if (selectedSpace->movePiece(targetDestination)) { //if valid move
				targetDestination->setPiece(selectedSpace->getPiece());
				selectedSpace->setPiece(nullptr);
				std::cout << "\nvalid operation.";
				Sleep(500);
				moved = true;

			}
			else {
				std::cout << "invalid operation.";
				Sleep(500);
			}
			Sleep(500);
			system("cls");
			print();
			Sleep(500);
		}
		
	} //gameloop

}

void Chessboard::generate() {
	grid = new Space * [8]; // dynamically allocate 8 rows
	for (int i{ 0 }; i < 8; ++i) { //populate chessboard with empty space objects ( 8 x 8 )
		grid[i] = new Space[8]; 
	} 

	for (int o{ 0 }; o < 8; ++o) {
		for (int i{ 0 }; i < 8; ++i) {
			grid[o][i] = Space();
			grid[o][i].setX(o);
			grid[o][i].setY(i);
		}
	}
	Space* current{ nullptr };
	int color;
	for (int o{ 0 }; o < 8; ++o) {
		for (int i{ 0 }; i < 8; ++i) {
			current = &grid[o][i];
			if (o == 0 || o == 1) { // if black
				color = black;
			}
			else if (o == 6 || o == 7){ // if white
				color = white;
			}
			else {
				color = none;
			}
			current->setPiece(o, i, color);
		}
	}
}

void Chessboard::print() {
	Piece* piecePtr{ nullptr };
	char symbol{' '};
	std::cout << "\n";
	std::cout << "       ";
	for (int i{ 0 }; i < 8; ++i) { //display letter coordinates 
		std::cout << letterPositions.at(i) << "     ";
	}
	std::cout << "\n\n";
	for (int o{ 0 }; o < 8; ++o) {
		std::cout << "  " << o << "  "; //display number coordinates
		for (int i{ 0 }; i < 8; ++i ) {
			if (grid[o][i].getPiece() != nullptr) { //if space not empty
				piecePtr = grid[o][i].getPiece();
				symbol = piecePtr->getSymbol();
				if ( piecePtr->getColor() == white ) { // if white
					symbol = toupper(symbol); //make symbol uppercase
				}
				std::cout << "| " << symbol << " | ";
			}
			else {
				std::cout << "| ~ | ";
			}
			piecePtr = nullptr;
			symbol = ' ';
		}
		std::cout << "\n\n";
	}
}

bool Chessboard::printHelp() {
	std::cout << "\n[KEY]: \n";
	std::cout << "\n uppercase = white \n lowercase = black";

	std::cout << "\n\n [p] = pawn";
	std::cout << "\n [r] = rook";
	std::cout << "\n [h] = knight";
	std::cout << "\n [b] = bishop";
	std::cout << "\n [q] = queen";
	std::cout << "\n [k] = king";

	std::cout << "\n\nyou can open this menu at anytime by typing 'help'.";
	std::cout << "\ntype 'exit' to dismiss this menu: ";

	std::string userInput{""};
	while (true) {
		std::cin >> userInput;
		if ( std::cin.fail() ) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max());
		}
		else {
			std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
			if (userInput == "EXIT") {
				system("cls");
				Sleep(200);
				print();
				Sleep(1000);
				break;
			}
		}
		
	}
	return true;
}

Space* Chessboard::getUserSelectedSpace() {
	Space* userSelectedSpace = nullptr;
	char letterPos{};
	int numberPos{-1};

	bool valid{ false };
	std::cout << "\nenter the letter coordinate: ";
	while (!valid) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cin >> letterPos;
		if (std::cin.fail()) {
			clearInputBuffer();
		}
		else {
			letterPos = tolower(letterPos);
			for (char c : letterPositions) {
				if (c == letterPos) {
					valid = true;
					break;
				} 
			}
		}
			
	}

	

	valid = false;
	std::cout << "enter the number coordinate: ";
	while (!valid ) {

		std::cin >> numberPos;
		if (std::cin.fail()) {
			clearInputBuffer();
		}
			if (numberPos < 8) {
				valid = true;
				break;
			}
	}
	
	system("cls"); //clear console output
	print();
	Sleep(500);

	int letterPosIntegerFormat{ 0 };
	switch (letterPos) {
	case 'a': 
		letterPosIntegerFormat = 0; break;
	case 'b':
		letterPosIntegerFormat = 1; break;
	case 'c':
		letterPosIntegerFormat = 2; break;
	case 'd':
		letterPosIntegerFormat = 3; break;
	case 'e':
		letterPosIntegerFormat = 4; break;
	case 'f':
		letterPosIntegerFormat = 5; break;
	case 'g':
		letterPosIntegerFormat = 6; break;
	case 'h':
		letterPosIntegerFormat = 7; break;
	}

	std::cout << " You selected [" << letterPos << ", " << numberPos << "]";
	userSelectedSpace = &grid[numberPos][letterPosIntegerFormat];
	
	return userSelectedSpace;
}

void Chessboard::clearInputBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Chessboard::displayCurrentTurn() {
	std::string currentColor;
	if (currentColorsTurn == white) { //if white
		currentColor = "white";
	}
	else { //if black
		currentColor = "black";
	}
	std::cout << "[ " << currentColor << "'s ] turn : total moves [" << turn << "]"; //display current turn and total moves made
}
