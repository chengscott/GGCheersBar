#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "go.h"

int main() {
	{
		using namespace GGCheersBar;
		Go g(Black, Position(7, 6));
		g.set(Position(1, 1), Black);
		g.set(Position(2, 2), Black);
		g.set(Position(3, 3), Black);
		g.set(Position(4, 4), Black);
		g.set(Position(5, 4), Black);
		g.set(Position(14, 0), Black);
		g.set(Position(7, 6), White);
		g.set(Position(8, 6), White);
		g.set(Position(9, 6), White);
		g.set(Position(10, 6), White);
		g.set(Position(11, 6), White);
		printf("%d", g.Judge() == Lose);
	};
	return 0;
}