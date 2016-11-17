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
		const int currow = curpos_.getX(), curcol = curpos_.getY();
		const Chess curchess = board_[currow][curcol];
		if (curchess == Null) return On;
		// has five
		std::vector<int> count = GetLine(curpos_, curchess);
		if (count[0] > 0) return isWin(curchess);
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
	std::vector<Position> Go::GetAchilles() const {
		std::vector<Position> moves;
		std::map<int, Position, std::greater<int>> weighted_moves;
		const Chess opp_chess = chess_ == Black ? White : Black;
		if (board_[curpos_.getX()][curpos_.getY()] == Null)
			moves.push_back(curpos_);
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (board_[i][j] != Null) continue;
				std::vector<int> countSelf = GetLine(Position(i, j), chess_);
				std::vector<int> countOpp = GetLine(Position(i, j), opp_chess);
				int exploitation =
					countSelf[0] * 87654321 +
					countOpp[0] * 7654321 +
					countSelf[1] * 654321 +
					countOpp[1] * 654321 +
					countSelf[2] * 54321 +
					countOpp[2] * 321 +
					countSelf[3] * 4321;
				if (exploitation > 0) {
					int exploration =
						countOpp[3] * 3 +
						countSelf[4] * 5 +
						countSelf[5] * 5 +
						countOpp[4] * 1+
						countOpp[5] * 4;
					weighted_moves[exploitation + exploration] = Position(i, j);
				}
			}
		}
		for (auto itr : weighted_moves) moves.push_back(itr.second);
		return moves;
	}
	std::vector<Position> Go::GetMoves() const {
		std::vector<Position> moves;
		// TODO: heuristics
		if (board_[curpos_.getX()][curpos_.getY()] == Null)
			moves.push_back(curpos_);
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (board_[i][j] != Null) continue;
				if ((i > 0 && board_[i - 1][j] != Null) ||
					(i < 14 && board_[i + 1][j] != Null) ||
					(j > 0 && board_[i][j - 1] != Null) ||
					(j < 14 && board_[i][j + 1] != Null) ||
					(i > 0 && j > 0 && board_[i - 1][j - 1] != Null) ||
					(i < 14 && j < 14 && board_[i + 1][j + 1] != Null) ||
					(i < 14 && j > 0 && board_[i + 1][j - 1] != Null) ||
					(i > 0 && j < 14 && board_[i - 1][j + 1] != Null)
					) {
					moves.push_back(Position(i, j));
				}
			}
		}
		return moves;
	}
	void Go::Simulation() {
		// HACK: heuristics
		Move(GetMoves()[0]);
	}
	// @return {5, live 4, dead 4, live 3, dead 3, live 2}
	std::vector<int> Go::GetLine(const Position& pos, const Chess& curchess) const {
		const int currow = pos.getX(), curcol = pos.getY();
		int col, row, stat[8] = {};
		// state : {col, col_avbl, row, row_avbl, diag, diag_avbl, adiag, adiag_avbl}
		// column
		int left = 0, right = 0;
		for (col = curcol - 1; col >= 0 && board_[currow][col] == curchess; --col) left++;
		stat[1] = col >= 0 && board_[currow][col] == Null;
		for (col = curcol + 1; col < 15 && board_[currow][col] == curchess; ++col) right++;
		stat[1] += col < 15 && board_[currow][col] == Null;
		stat[0] = left + 1 + right;
		// row
		int up = 0, down = 0;
		for (row = currow - 1; row >= 0 && board_[row][curcol] == curchess; --row) up++;
		stat[3] = row >= 0 && board_[row][curcol] == Null;
		for (row = currow + 1; row < 15 && board_[row][curcol] == curchess; ++row) down++;
		stat[3] += row < 15 && board_[row][curcol] == Null;
		stat[2] = up + 1 + down;
		// diagonal
		up = 0; down = 0;
		for (row = currow - 1, col = curcol - 1; row >= 0 && col >= 0 && board_[row][col] == curchess; --row, --col) up++;
		stat[5] = row >= 0 && col >= 0 && board_[row][col] == Null;
		for (row = currow + 1, col = curcol + 1; row < 15 && col < 15 && board_[row][col] == curchess; ++row, ++col) down++;
		stat[5] += row < 15 && col < 15 && board_[row][col] == Null;
		stat[4] = up + 1 + down;
		// antidiagonal
		up = 0; down = 0;
		for (row = currow + 1, col = curcol - 1; row < 15 && col >= 0 && board_[row][col] == curchess; ++row, --col) up++;
		stat[7] = row < 15 && col >= 0 && board_[row][col] == Null;
		for (row = currow - 1, col = curcol + 1; row >= 0 && col < 15 && board_[row][col] == curchess; --row, ++col) down++;
		stat[7] += row >= 0 && col < 15 && board_[row][col] == Null;
		stat[6] = up + 1 + down;
		std::vector<int> ret(6, 0);
		// {5, live 4, dead 4, live 3, dead 3, live 2}
		for (int i = 0; i < 8; i += 2) {
			ret[0] += stat[i] >= 5;
			ret[1] += stat[i] == 4 && stat[i + 1] == 2;
			ret[2] += stat[i] == 4 && stat[i + 1] == 1;
			ret[3] += stat[i] == 3 && stat[i + 1] == 2;
			ret[4] += stat[i] == 3 && stat[i + 1] == 1;
			ret[5] += stat[i] == 3 && stat[i + 1] == 2;
		}
		return ret;
	}
}