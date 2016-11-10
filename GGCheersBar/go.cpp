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
	State Go::Judge() const {
		// has five
		int currow = curpos_.getX(), curcol = curpos_.getY();
		Chess curchess = board_[currow][curcol];
		int* count = GetLine(curpos_, curchess);
		if (count[5] > 0) return isWin(curchess);
		// has Null
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				if (board_[i][j] == Null)
					return On;
		return Draw;
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
	State Go::isWin(const Chess& c) const {
		return c == chess_ ? Win : Lose;
	}
	Chess Go::getChess() const { return chess_; }
	void Go::Move(const Position& move) {
		board_[move.getX()][move.getY()] = chess_;
		chess_ = chess_ == Black ? White : Black;
		curpos_ = move;
	}
	std::vector<Position> Go::GetMoves() const {
		std::vector<Position> moves;
		// TODO
		return moves;
	}
}