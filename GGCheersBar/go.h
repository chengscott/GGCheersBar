#ifndef GO_Def
#define GO_Def
#include "util.h"
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

namespace GGCheersBar {
	class Go {
	public:
		Go();
		Go(const Chess, const Position = NotFound);
		Chess getBoardChess(const Position&) const;
		Chess getChess() const;
		State Judge() const;
		void Move(const Position&);
		std::vector<Position> GetAchilles() const;
		std::vector<Position> GetMoves() const;
		void Simulation();
	private:
		std::vector<int> GetLine(const Position&, const Chess&) const;
		State isWin(const Chess&) const;
		Chess board_[15][15], chess_;
		Position curpos_;
	};
}
#endif