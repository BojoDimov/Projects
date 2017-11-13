#include <iostream>
#include <vector>
#include <string>

#define BOARD_SIZE 3
#define COMPUTER 1
#define PLAYER 2
#define EMPTY 0

typedef std::vector<std::vector<int>> Board;

struct Node {
	int data;
	Board board;
};

int alphaBeta(Node* node, bool maxTurn) {
	/*int res;
	if (node->children.size() == 0) return node->data;*/
}

void print_board(Board& b) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (b[i][j] == 0) std::cout << "_ ";
			else if (b[i][j] == 1) std::cout << "X ";
			else std::cout << "O ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

int check_state(Board& b, int marker) {
	return 0;
}

int computer_turn(Board& b) {
	return check_state(b, COMPUTER);
}

int player_turn(Board& b, int x, int y) {
	if (b[y][x] != EMPTY) {
		std::cerr << "INVALID MOVE";
		throw "INVALID MOVE";
	}
	b[y][x] == PLAYER;
	return check_state(b, PLAYER);
}

int main() {
	int x, y, state_value = 0;
	do {
		Board board;
		std::cin >> x >> y;
		state_value = player_turn(board, x, y);
		print_board(board);
		state_value = computer_turn(board);
		print_board(board);
	} while (state_value == 0);
	if (state_value == 1) std::cout << "\nYou lost!\n";
	else std::cout << "\nYou won!\n";
	return 0;
}