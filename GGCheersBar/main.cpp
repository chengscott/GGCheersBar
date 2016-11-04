#include <cstdio>
#include "go.h"

int main() {
	{
		using namespace GGCheersBar;
		Go g;
		g.set(Position(1, 1), Black);
		g.set(Position(2, 2), Black);
		g.set(Position(3, 3), Black);
		g.set(Position(4, 4), Black);
		g.set(Position(5, 5), Black);
		printf("%d", g.get(Position(3, 4)) == Black);
	};
	return 0;
}