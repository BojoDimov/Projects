#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#define COMPUTER 1
#define PLAYER -1
#define EMPTY 0
#define WIN 1
#define DRAW 0
#define ONGOING 2
#define MIN -2
#define MAX 2

typedef std::vector<std::vector<int>> Board;

struct State {
	int data;
	Board board;
};

int max(Board& b, int alpha, int beta);
int min(Board& b, int alpha, int beta);
int check_state(Board& b);

int max(Board& b, int alpha, int beta) {
	auto value = check_state(b);
	if (value != ONGOING) {
		return value;
	}

	auto best_val = MIN;
	int max_i = 0, max_j = 0;
	Board copy_board;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] == EMPTY) {
				copy_board = b;
				copy_board[i][j] = COMPUTER;

				auto val = min(copy_board, alpha, beta);
				if (val > best_val) {
					best_val = val;
					max_i = i;
					max_j = j;
				}

				if (val > beta) {
					break;
				}

				if (val > alpha) {
					alpha = val;
				}
			}
		}
	}

	b[max_i][max_j] = COMPUTER;
	return best_val;
}

int min(Board& b, int alpha, int beta) {
	auto value = check_state(b);
	if (value != ONGOING) {
		return value;
	}

	auto best_val = MAX;
	int max_i = 0, max_j = 0;
	Board copy_board;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] == EMPTY) {
				copy_board = b;
				copy_board[i][j] = PLAYER;

				auto val = max(copy_board, alpha, beta);

				if (val < best_val) {
					best_val = val;
					max_i = i;
					max_j = j;
				}

				if (val < alpha) {
					break;
				}

				if (val < beta) {
					beta = val;
				}
			}
		}
	}
	b[max_i][max_j] = PLAYER;
	return best_val;
}

int check_state(Board& b) {
	if ((b[0][0] == COMPUTER && b[1][1] == COMPUTER && b[2][2] == COMPUTER)
		|| (b[0][2] == COMPUTER && b[1][1] == COMPUTER && b[2][0] == COMPUTER)) return COMPUTER;

	if ((b[0][0] == PLAYER && b[1][1] == PLAYER && b[2][2] == PLAYER)
		|| (b[0][2] == PLAYER && b[1][1] == PLAYER && b[2][0] == PLAYER)) return PLAYER;

	for (int i = 0; i < 3; i++) {
		if ((b[i][0] == COMPUTER && b[i][1] == COMPUTER && b[i][2] == COMPUTER)
			|| (b[0][i] == COMPUTER && b[1][i] == COMPUTER && b[2][i] == COMPUTER)) return COMPUTER;
	}

	for (int i = 0; i < 3; i++) {
		if ((b[i][0] == PLAYER && b[i][1] == PLAYER && b[i][2] == PLAYER)
			|| (b[0][i] == PLAYER && b[1][i] == PLAYER && b[2][i] == PLAYER)) return PLAYER;
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (b[i][j] == EMPTY) return ONGOING;
		}
	}

	return DRAW;
}

int computer_turn(Board& b) {
	auto t1 = clock();
	max(b, MIN, MAX);
	auto res = check_state(b);
	//std::cout << "Calculation time for the turn: " << clock() - t1 << "ms\n";
	return res;
}

int player_turn(Board& b, int x, int y) {
	if (b[y][x] != EMPTY) {
		std::cerr << "INVALID MOVE";
		throw "INVALID MOVE";
	}
	b[y][x] = PLAYER;
	return check_state(b);
}

void init_board(Board& b) {
	for (int i = 0; i < 3; i++) {
		std::vector<int> row;
		for (int j = 0; j < 3; j++) {
			row.push_back(EMPTY);
		}
		b.push_back(row);
	}
}

void print_board(Board& b) {
	for (int i = 0; i < b.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			if (b[i][j] == 0) std::cout << "- ";
			else if (b[i][j] == 1) std::cout << "x ";
			else std::cout << "o ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

void game_loop(Board& b) {
	int x, y, game_state = 0;
	do {
		std::cout << "Enter coordinates:\n";
		std::cin >> x >> y;
		game_state = player_turn(b, x-1, y-1);
		print_board(b);
		if (game_state != ONGOING) break;

		game_state = computer_turn(b);
		print_board(b);
	} while (game_state == ONGOING);

	if (game_state == COMPUTER) std::cout << "\nYou lost!\n";
	else if (game_state == PLAYER) std::cout << "\nYou won!\n";
	else std::cout << "\nDraw!\n";
}

int main() {
	Board board;
	init_board(board);
	game_loop(board);
	return 0;
}