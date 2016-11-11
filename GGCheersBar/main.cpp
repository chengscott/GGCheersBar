#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <chrono>
#include "go.h"
#include "mcts.h"
using namespace std::chrono;
using namespace GGCheersBar;

Position readPosition();
int main() {
	Go go(Black, Position(8, 7));
	Chess AI;
	State judge;
	Position move;
	int option = -1;
	while (option != 0 && option != 1) {
		printf("AI plays first [1/0]? ");
		scanf("%d", &option);
		// directly setup
		if (option == 2) {
			do {
				move = readPosition();
			} while (go.getBoardChess(move) != Null);
			go.Move(move);
		}
	}
	AI = option == 1 ? Black : White;
	while ((judge = go.Judge()) == On) {
		if (go.getChess() == AI) {
			auto start_time = high_resolution_clock::now();
			move = MCTS::ComputeMove(go);
			auto end_time = high_resolution_clock::now();
			double dt = 1.e-9*duration_cast<nanoseconds>(end_time - start_time).count();
			printf(" Spend: %.3fs\n", dt);
		} else {
			do {
				move = readPosition();
			} while (go.getBoardChess(move) != Null);
		}
		printf("[%s] (%c, %d)\n",
			CHESS[go.getChess()], char(move.getX() + 'A'), move.getY());
		go.Move(move);
	}
	switch (judge) {
	case Win:
		printf("\n\n[%s] Win", CHESS[go.getChess()]);
		break;
	case Lose:
		printf("\n\n[%s] Lose", CHESS[go.getChess()]);
		break;
	case Draw:
		printf("\n\nDraw");
		break;
	}
	scanf("%d", &option);
	return 0;
}

Position readPosition() {
	char row_ch;
	int row, col;
	scanf(" %c %d", &row_ch, &col);
	row = row_ch - 'A';
	return Position(row, col);
}