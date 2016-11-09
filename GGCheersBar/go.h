#include "util.h"

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
	private:
		State isWin(const Chess&) const;
		Chess board_[15][15], chess_;
		Position curpos_;
	};
}