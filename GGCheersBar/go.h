#include "util.h"
#ifndef GO_Def
#define GO_Def
#include <vector>

namespace GGCheersBar {
	class Go {
	public:
		Go();
		Go(const Chess, const Position);
		State Judge() const;
		void set(const Position&);
		void set(const Position&, const Chess);
		Chess get(const Position&) const;
		Chess getChess() const;
		std::vector<Position> GetMoves() const;
	private:
		int* GetLine(const Position&, const Chess&) const;
		State isWin(const Chess&) const;
		Chess board_[15][15], chess_;
		Position curpos_;
	};
}
#endif