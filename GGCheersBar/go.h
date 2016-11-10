#ifndef GO_Def
#define GO_Def
#include "util.h"
#include <vector>

namespace GGCheersBar {
	class Go {
	public:
		Go();
		Go(const Chess, const Position = NotFound);
		Chess getChess() const;
		State Judge() const;
		void Move(const Position&);
		std::vector<Position> GetMoves() const;
	private:
		int* GetLine(const Position&, const Chess&) const;
		State isWin(const Chess&) const;
		Chess board_[15][15], chess_;
		Position curpos_;
	};
}
#endif