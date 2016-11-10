#ifndef UTIL_Def
#define UTIL_Def
#include <random>

namespace GGCheersBar {
	class Position {
	public:
		Position() {}
		Position(const Position&);
		Position(const int&, const int&);
		~Position() {}
		int getX() const;
		int getY() const;
		bool operator<(const Position&) const;
		Position& operator=(const Position&);
		bool operator==(const Position&) const;
		bool operator!=(const Position&) const;
	private:
		int x_, y_;
	};
	Position const NotFound(-1, -1);
	enum Chess { Black, White, Null };
	enum State { Win, Lose, Draw, On };
	int random(int a, int b);
}
#endif