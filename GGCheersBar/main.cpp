#pragma comment(lib, "ws2_32.lib") 
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <chrono>
#include "go.h"
#include "mcts.h"
#include <winsock2.h>
using namespace std::chrono;
using namespace GGCheersBar;
#define MAX_SIZE 2048

Position readPosition();
int main() {
	/****Socket****/
	SOCKET serverSocket, clientSocket;
	struct sockaddr_in serverAddress, clientAddress;
	int clientAddressLen;
	int bytesRead;
	char buf[MAX_SIZE], instr[MAX_SIZE], instr_cplmt[MAX_SIZE];
	int SERVER_PORT;
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), (LPWSADATA)&wsadata) != 0) {
		// MY_ERROR("Winsock Error\n");
	}
	char name[50];
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	while (1) {
		gets_s(instr);
		scanf(instr, "%s [%d]", name, &SERVER_PORT);
		std::string inst(name);
		if (inst == "begin") {
			break;
		}
		else {
			printf("Input is error.\n");
		}
	}
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(SERVER_PORT);

	if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
		// MY_ERROR("Bind Error\n");
	}

	if (listen(serverSocket, 3) < 0) {
		// MY_ERROR("Listen Error\n");
	}
	/*************/
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