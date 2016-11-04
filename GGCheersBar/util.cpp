#include "util.h"

namespace GGCheersBar {
	Position::Position(const Position & rhs) {
		x_ = rhs.getX();
		y_ = rhs.getY();
	}
	Position::Position(const int& x, const int& y) { x_ = x, y_ = y; }
	int Position::getX() const { return x_; }
	int Position::getY() const { return y_; }
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
	int random_int() {
		int seed = 20161029;
		return seed += (seed << 16) + 0x1db3d743;
	}
	long long random_long_long() {
		long long seed = 20161029;
		return seed += (seed << 32) + 0xdb3d742c265539d;
	}
}