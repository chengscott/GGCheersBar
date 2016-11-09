#include "util.h"
#ifndef go
#define go
namespace GGCheersBar {
	class Go {
	public:
		Go();
		Go(const Chess, const Position);
		~Go();
		State Judge() const;
		void set(const Position&);
		void set(const Position&, const Chess);
		Chess get(const Position&) const;
		// priority_queue<Position> GetAvailableMove() const;
	private:
		int* GetLine(const Position&, const Chess&) const;
		State isWin(const Chess&) const;
		Chess board_[15][15], chess_;
		Position curpos_;
	};
}
#endif