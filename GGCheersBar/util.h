#ifndef UTIL_Def
#define UTIL_Def

namespace GGCheersBar {
	static const char* CHESS[] = { "Black", "White", "Null" };
	enum Chess { Black, White, Null };
	enum State { Win, Lose, Draw, On };
	class Position {
	public:
		Position() {}
		Position(const Position&);
		Position(const int&, const int&);
		Position& operator=(const Position&);
		~Position() {}
		int getX() const;
		int getY() const;
		bool operator<(const Position&) const;
		bool operator==(const Position&) const;
		bool operator!=(const Position&) const;
	private:
		int x_, y_;
	};
	static const Position NotFound(-1, -1);
}
#endif