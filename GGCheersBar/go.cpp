#include "go.h"

namespace GGCheersBar {
	Go::Go() {
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				board_[i][j] = Null;
	}
	Go::Go(const Chess c) {
		chess_ = c;
		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				board_[i][j] = Null;
	}
	Go::~Go() { }
	State Go::Judge() const {
		// TODO
		return On;
	}
	Position Go::Play() {
		// TODO
		Position res;
		res = threat();
		if (res != NotFound)
			return res;
		return res;
	}
	void Go::set(const Position& p) {
		set(p, chess_);
	}
	void Go::set(const Position& p, const Chess c) {
		board_[p.getX()][p.getY()] = c;
	}
	Chess Go::get(const Position& p) const {
		return board_[p.getX()][p.getY()];
	}
	// strategy
	Position Go::threat() {
		// TODO
		return NotFound;
	}
}