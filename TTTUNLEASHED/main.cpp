#include <iostream>
#include <conio.h>
#include <stdlib.h>


#define PLAYERCHAR1		'X'
#define PLAYERCHAR2		'O'

#define BOARDSIZE 3

using std::cout;
using std::cin;

//Function displays the playing grid and the current marks on the board
void drawBoard (char board[BOARDSIZE][BOARDSIZE], char player) {

	system("CLS");

	cout << "Press the corresponding number to play your turn.\n";
	cout << "PLAYER: " << player << "\n\n";

	cout << "\t\t\t" << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << "\n";
	cout << "\t\t\t" << "-+-+-\n";
	cout << "\t\t\t" << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << "\n";
	cout << "\t\t\t" << "-+-+-\n";
	cout << "\t\t\t" << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << "\n";
	cout << "\n\n\n";

	return;
}

void switchPlayer(char* player) {
	if (*player == PLAYERCHAR1) {
		*player = PLAYERCHAR2;
	}
	else {
		*player = PLAYERCHAR1;
	}
}

void initialize(char board[BOARDSIZE][BOARDSIZE]) {
	int placement = 1;
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			board[i][j] = '0'+ placement;
			placement++;
		}
	}
}

bool checkWin (char board[BOARDSIZE][BOARDSIZE]) {

	//Check horizontal
	for (int i = 0; i < BOARDSIZE; i++) {
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2]) {
			return true;
		}
	}

	//Check vertical
	for (int i = 0; i < BOARDSIZE; i++) {
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i]) {
			return true;
		}
	}

	//Check diagonal
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2]) {
		return true;
	}
	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0]) {
		return true;
	}

	return false;
}
bool checkDraw(char board[BOARDSIZE][BOARDSIZE]) {
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			if (board[i][j] != PLAYERCHAR1 && board[i][j] != PLAYERCHAR2) {
				return false;
			}
		}
	 }
	return true;
}

bool validMove(char board[BOARDSIZE][BOARDSIZE], int move[]) {
	if ((board[move[0]][move[1]] >= '0' + 1) && (board[move[0]][move[1]] <= '1' + 8)) {
		return true;
	}
	return false;
}

void interpreter(char select, int coords[]) {
	switch (select) {
	case '1':
		coords[0] = 0;
		coords[1] = 0;
		break;
	case '2':
		coords[0] = 0;
		coords[1] = 1;
		break;
	case '3':
		coords[0] = 0;
		coords[1] = 2;
		break;
	case '4':
		coords[0] = 1;
		coords[1] = 0;
		break;
	case '5':
		coords[0] = 1;
		coords[1] = 1;
		break;
	case '6':
		coords[0] = 1;
		coords[1] = 2;
		break;
	case '7':
		coords[0] = 2;
		coords[1] = 0;
		break;
	case '8':
		coords[0] = 2;
		coords[1] = 1;
		break;
	case '9':
		coords[0] = 2;
		coords[1] = 2;
		break;
	default:
		coords[0] = -1;
		coords[1] = -1;
	}
}

void playerMove(char board[][BOARDSIZE], char player) {

	int spot[2];

	while (true) {
		cout << ">> ";
		char select = _getch();
		interpreter(select, spot);
		if (validMove(board, spot)) {
			board[spot[0]][spot[1]] = player;
			break;
		}
		else {
			cout << "Invalid move!\n\n";
		}
	}
}


char mainMenu() {
	cout << "Press the corresponding number to continue.\n\n";

	cout << "1). Player Vs. Player\n";
	cout << "2). Quit\n\n\n";

	char select = _getch();

	return select;
}

void gameLoop(int gameMode) {

	char board[BOARDSIZE][BOARDSIZE];
	char player = PLAYERCHAR1;
	bool gameOver = false;
	int turns = 0;

	initialize(board);

	while (gameOver == false) {
		
		drawBoard(board, player);
		playerMove(board, player);

		if (checkWin(board)) {
			gameOver = true;
			drawBoard(board, player);
			cout << "Congratulations player " << player << ", you won!\n\n";
			cout << "Press any key to return to the main menu...";
			_getch();
		}
		if (checkDraw(board) && gameOver != true) {
			gameOver = true;
			drawBoard(board, player);
			cout << "It's a Draw!\n\n";
			cout << "Press any key to return to the main menu...";
			_getch();
		}
		switchPlayer(&player);


	}

}

int main() {
	bool quit = false;
	while (quit == false) {
		system("CLS");
		switch (mainMenu()) {
		case '1':
			gameLoop(1);
			break;
		case '2':
			quit = true;
			break;
		default:
			cout << "Invalid key!\n\n\n";
		}
	}
}