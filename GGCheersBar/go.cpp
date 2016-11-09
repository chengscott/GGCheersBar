#include "go.h"

namespace GGCheersBar {
	Go::Go() {
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				board_[i][j] = Null;
		chess_ = Null;
		curpos_ = NotFound;
	}
	Go::Go(const Chess c, const Position p = NotFound) {
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				board_[i][j] = Null;
		chess_ = c;
		curpos_ = p;
	}
	Go::~Go() { }
	State Go::Judge() const {
		int currow = curpos_.getX(), curcol = curpos_.getY();
		Chess curchess = board_[currow][curcol];
		// five in a column
		int left = 0, right = 0;
		for (int col = curcol - 1; col >= 0 && board_[currow][col] == curchess; --col) left++;
		for (int col = curcol + 1; col < 15 && board_[currow][col] == curchess; ++col) right++;
		if (left + 1 + right >= 5) return isWin(curchess);
		// five in a row
		int up = 0, down = 0;
		for (int row = currow - 1; row >= 0 && board_[row][curcol] == curchess; --row) up++;
		for (int row = currow + 1; row < 15 && board_[row][curcol] == curchess; ++row) down++;
		if (up + 1 + down >= 5) return isWin(curchess);
		// five in a diagonal
		up = 0; down = 0;
		for (int row = currow - 1, col = curcol - 1; row >= 0 && col >= 0 && board_[row][col] == curchess; --row, --col) up++;
		for (int row = currow + 1, col = curcol + 1; row < 15 && col < 15 && board_[row][col] == curchess; ++row, ++col) down++;
		if (up + 1 + down >= 5) return isWin(curchess);
		// five in an antidiagonal
		up = 0; down = 0;
		for (int row = currow + 1, col = curcol - 1; row < 15 && col >= 0 && board_[row][col] == curchess; ++row, --col) up++;
		for (int row = currow - 1, col = curcol + 1; row >= 0 && col < 15 && board_[row][col] == curchess; --row, ++col) down++;
		if (up + 1 + down >= 5) return isWin(curchess);
		// has Null
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				if (board_[i][j] == Null)
					return On;
		return Draw;
	}
	State Go::isWin(const Chess& c) const {
		return c == chess_ ? Win : Lose;
	}
	void Go::set(const Position& p) {
		set(p, chess_);
	}
	void Go::set(const Position& p, const Chess c) {
		board_[p.getX()][p.getY()] = c;
	}
	Chess Go::get(const Position& p) const {
		return board_[p.getX()][p.getY()];
	}
}