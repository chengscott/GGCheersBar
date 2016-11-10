#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include "go.h"
#include "mcts.h"
using namespace GGCheersBar;

int main() {
	Chess AI;
	int chess;
	scanf("%d", &chess);
	AI = chess == 0 ? Black : White;
	Go go(Black);
	Position move;
	while (go.Judge() == On) {
		if (go.getChess() == AI) {
			move = MCTS::ComputeMove(go);
		} else {
			char row; int col;
			scanf("%c%d", &row, &col);
			move = Position(row, col);
		}
		go.Move(move);
	}
	// output
	// go.Judge()
	return 0;
}