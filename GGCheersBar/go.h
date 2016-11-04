#include "util.h"

namespace GGCheersBar {
	class Go {
	public:
		Go();
		Go(const Chess c);
		~Go();
		State Judge() const;
		Position Play();
		void set(const Position&);
		void set(const Position&, const Chess c);
		Chess get(const Position&) const;
	private:
		Chess board_[15][15], chess_;
		Position threat();
	};
}