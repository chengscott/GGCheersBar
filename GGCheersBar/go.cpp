#include "go.h"

namespace GGCheersBar {
	Go::Go() {
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				board_[i][j] = Null;
		chess_ = Null;
		curpos_ = NotFound;
	}
	Go::Go(const Chess c, const Position p) {
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				board_[i][j] = Null;
		chess_ = c;
		curpos_ = p;
	}
	Chess Go::getBoardChess(const Position& pos) const {
		return board_[pos.getX()][pos.getY()];
	}
	Chess Go::getChess() const { return chess_; }
	State Go::Judge() const {
		int currow = curpos_.getX(), curcol = curpos_.getY();
		Chess curchess = board_[currow][curcol];
		if (curchess == Null) return On;
		// has five
		int* count = GetLine(curpos_, curchess);
		if (count[5] > 0) return isWin(curchess);
		// has Null
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				if (board_[i][j] == Null)
					return On;
		return Draw;
	}
	State Go::isWin(const Chess& c) const { return c == chess_ ? Win : Lose; }
	void Go::Move(const Position& move) {
		board_[move.getX()][move.getY()] = chess_;
		chess_ = chess_ == Black ? White : Black;
		curpos_ = move;
	}
	std::vector<Position> Go::GetMoves() const {
		std::vector<Position> moves;
		// TODO: heuristics
		if (board_[curpos_.getX()][curpos_.getY()] == Null)
			moves.push_back(curpos_);
		// Near two
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j) {
				if (board_[i][j] == Null && (
						(i > 0 && board_[i - 1][j] != Null) ||
						(i > 1 && board_[i - 2][j] != Null) ||
						(i < 14 && board_[i + 1][j] != Null) ||
						(i < 13 && board_[i + 2][j] != Null) ||
						(j > 0 && board_[i][j - 1] != Null) ||
						(j > 1 && board_[i][j - 2] != Null) ||
						(j < 14 && board_[i][j + 1] != Null) ||
						(j < 13 && board_[i][j + 2] != Null)
					)
				   )
					moves.push_back(Position(i, j));
			}
		std::random_device rnd;
		std::mt19937 twist(rnd());
		std::shuffle(moves.begin(), moves.end(), twist);
		return moves;
	}
	void Go::Simulation() {
		// HACK: heuristics
		Move(GetMoves()[0]);
	}
	// @return {-1, -1, 2, 3, 4, >=5}
	int* Go::GetLine(const Position& pos, const Chess& curchess) const {
		int currow = pos.getX(), curcol = pos.getY(), count[6] = { -1, -1, 0, 0, 0, 0 };
		// column
		int left = 0, right = 0;
		for (int col = curcol - 1; col >= 0 && board_[currow][col] == curchess; --col) left++;
		for (int col = curcol + 1; col < 15 && board_[currow][col] == curchess; ++col) right++;
		for (int i = 2; i < 5; ++i) count[i] += (left + 1 + right == i);
		count[5] += (left + 1 + right >= 5);
		// row
		int up = 0, down = 0;
		for (int row = currow - 1; row >= 0 && board_[row][curcol] == curchess; --row) up++;
		for (int row = currow + 1; row < 15 && board_[row][curcol] == curchess; ++row) down++;
		for (int i = 2; i < 5; ++i) count[i] += (up + 1 + down == i);
		count[5] += (up + 1 + down >= 5);
		// diagonal
		up = 0; down = 0;
		for (int row = currow - 1, col = curcol - 1; row >= 0 && col >= 0 && board_[row][col] == curchess; --row, --col) up++;
		for (int row = currow + 1, col = curcol + 1; row < 15 && col < 15 && board_[row][col] == curchess; ++row, ++col) down++;
		for (int i = 2; i < 5; ++i) count[i] += (up + 1 + down == i);
		count[5] += (up + 1 + down >= 5);
		// antidiagonal
		up = 0; down = 0;
		for (int row = currow + 1, col = curcol - 1; row < 15 && col >= 0 && board_[row][col] == curchess; ++row, --col) up++;
		for (int row = currow - 1, col = curcol + 1; row >= 0 && col < 15 && board_[row][col] == curchess; --row, ++col) down++;
		for (int i = 2; i < 5; ++i) count[i] += (up + 1 + down == i);
		count[5] += (up + 1 + down >= 5);
		for (int i = 5; i >= 2; --i) count[i] -= count[i - 1];
		return count;
	}
}