#pragma once
#include <iostream>
#include <vector>

class ConnectFour {
private:
	enum Piece {
		Empty = ' ',
		Player1 = 'X',
		Player2 = 'O'
	};
	enum GameStatus {
		NotStarted,
		InProgress,
		Player1Wins,
		Player2Wins,
		Draw
	};
	std::vector<std::vector<Piece>> board;
	GameStatus status;
	const int ROWS = 6;
	const int COLS = 7;
public:
	ConnectFour();
	GameStatus getStatus() const;
	bool printStatus();
	char pieceToChar(Piece piece) const;
	void display() const;
	Piece getCurrentPlayer();
	void printTurn();
	void play(int column);
	bool checkWin(Piece player);
	bool isBoardFull() const;
};