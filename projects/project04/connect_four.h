#pragma once
#include <iostream>
#include <vector>

class ConnectFour {
public:
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
	ConnectFour();
	GameStatus getStatus() const;
	void checkStatus();
	void setStatus(std::string input);
	bool printStatus();
	Piece getCurrentPlayer() const;
	void printTurn();
	void play(int column);
	bool checkWin(Piece player);
	bool isBoardFull() const;
	void resetBoard();
	Piece getPieceAt(int row, int col) const;
private:
	std::vector<std::vector<Piece>> board;
	GameStatus status;
	const int ROWS = 6;
	const int COLS = 7;
};