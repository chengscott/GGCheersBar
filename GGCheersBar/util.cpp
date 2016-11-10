#include "util.h"

namespace GGCheersBar {
	Position::Position(const Position & rhs) {
		x_ = rhs.getX();
		y_ = rhs.getY();
	}
	Position::Position(const int& x, const int& y) { x_ = x, y_ = y; }
	int Position::getX() const { return x_; }
	int Position::getY() const { return y_; }
	bool Position::operator<(const Position& rhs) const {
		return x_ < rhs.getX() || (x_ == rhs.getX() && y_ < rhs.getY());
	}
	Position& Position::operator=(const Position & rhs) {
		x_ = rhs.getX();
		y_ = rhs.getY();
		return *this;
	}
	bool Position::operator==(const Position & rhs) const {
		return (x_ == rhs.getX() && y_ == rhs.getY());
	}
	bool Position::operator!=(const Position & rhs) const {
		return (x_ != rhs.getX() || y_ != rhs.getY());
	}
	int random(int a, int b) {
		std::random_device rnd;
		std::mt19937 twist(rnd());
		std::uniform_int_distribution<> distr(a, b);
		return distr(twist);
	}
}