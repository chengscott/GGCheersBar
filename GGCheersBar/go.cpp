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
	std::vector<Position> Go::GetMoves() const {
		std::random_device rnd;
		std::mt19937 twist(rnd());
		std::uniform_real_distribution<> dist(0, 1.1);
		std::vector<Position> moves;
		std::map<double, Position> wtf_moves, weighted_moves;
		Chess opp_chess = chess_ == Black ? White : Black;
		// TODO: heuristics
		if (board_[curpos_.getX()][curpos_.getY()] == Null)
			moves.push_back(curpos_);
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (board_[i][j] != Null) continue;
				int* countSelf = GetLine(Position(i, j), chess_);
				int* countOpp = GetLine(Position(i, j), opp_chess);
				if (countSelf[6] == 0) continue;
				double exploitation =
					countSelf[1] * (1 << 20) +
					countSelf[2] * (1 << 20) +
					countOpp[1] * (1 << 25) +
					countOpp[2] * (1 << 25) +
					countOpp[3] * (1 << 10) +
					countSelf[3] * (1 << 1) -
					dist(twist);
				double exploration =
					countSelf[4] * (1 << 2) +
					countSelf[5] * (1 << 2) +
					countOpp[4] * (1 << 1) +
					countOpp[5] * (1 << 0) +
					dist(twist);
				if (exploitation > 0) wtf_moves[exploitation] = Position(i, j);
				else weighted_moves[exploration] = Position(i, j);
			}
		}
		for (auto itr : wtf_moves) moves.push_back(itr.second);
		for (auto itr : weighted_moves) moves.push_back(itr.second);
		return moves;
	}
	void Go::Simulation() {
		// HACK: heuristics
		// TODO: Not Found
		Move(GetMoves()[0]);
	}
	// @return {5, live 4, dead 4, live 3, dead 3, live 2, near 2}
	int* Go::GetLine(const Position& pos, const Chess& curchess) const {
		int currow = pos.getX(), curcol = pos.getY(), stat[8];
		// state : {col, col_avbl, row, row_avbl, diag, diag_avbl, adiag, adiag_avbl}
		// column
		int left = 0, right = 0;
		for (int col = curcol - 1; col >= 0 && board_[currow][col] == curchess; --col) left++;
		for (int col = curcol + 1; col < 15 && board_[currow][col] == curchess; ++col) right++;
		stat[0] = left + 1 + right;
		stat[1] = (board_[currow][curcol - left] == Null) + (board_[currow][curcol + right] == Null);
		// row
		int up = 0, down = 0;
		for (int row = currow - 1; row >= 0 && board_[row][curcol] == curchess; --row) up++;
		for (int row = currow + 1; row < 15 && board_[row][curcol] == curchess; ++row) down++;
		stat[2] = up + 1 +down;
		stat[3] = (board_[currow - up][curcol] == Null) + (board_[currow + down][curcol] == Null);
		// diagonal
		up = 0; down = 0;
		for (int row = currow - 1, col = curcol - 1; row >= 0 && col >= 0 && board_[row][col] == curchess; --row, --col) up++;
		for (int row = currow + 1, col = curcol + 1; row < 15 && col < 15 && board_[row][col] == curchess; ++row, ++col) down++;
		stat[4] = up + 1 + down;
		stat[5] = (board_[currow - up][curcol - up] == Null) + (board_[currow + down][curcol + down] == Null);
		// antidiagonal
		up = 0; down = 0;
		for (int row = currow + 1, col = curcol - 1; row < 15 && col >= 0 && board_[row][col] == curchess; ++row, --col) up++;
		for (int row = currow - 1, col = curcol + 1; row >= 0 && col < 15 && board_[row][col] == curchess; --row, ++col) down++;
		stat[6] = up + 1 + down;
		stat[7] = (board_[currow + up][curcol - up] == Null) + (board_[currow - down][curcol + down] == Null);
		int ret[7] = {};
		// {5, live 4, dead 4, live 3, dead 3, live 2, near 2}
		for (int i = 0; i < 8; i += 2) {
			ret[0] += stat[i] >= 5;
			ret[1] += stat[i] == 4 && stat[i] == 2;
			ret[2] += stat[i] == 4 && stat[i] == 1;
			ret[3] += stat[i] == 3 && stat[i] == 2;
			ret[4] += stat[i] == 3 && stat[i] == 1;
			ret[5] += stat[i] == 3 && stat[i] == 2;
			ret[6] += stat[i] > 1 || (stat[i] == 1 && stat[i + 1] < 2);
		}
		return ret;
	}
}