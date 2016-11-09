#ifndef util
#define util
#include <random>

namespace GGCheersBar {
	class Position {
	public:
		Position() {}
		Position(const Position& rhs);
		Position(const int& x, const int& y);
		~Position() {}
		int getX() const;
		int getY() const;
		Position& operator=(const Position& rhs);
		bool operator==(const Position& rhs) const;
		bool operator!=(const Position& rhs) const;
	private:
		int x_, y_;
	};
	Position const NotFound(-1, -1);
	enum Chess { Black, White, Null };
	enum State { Win, Lose, Draw, On };
	int random(int a, int b);
}
#endif