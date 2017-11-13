#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>

/*
	N-queens problem
*/

struct Queen {
	int row;
	int col;
};

typedef std::vector<Queen> State;

int count(Queen& queen, State& state) {
	int result = 0;
	for (int i = 0; i < state.size(); i++) {
		if (queen.col == state[i].col && queen.row == state[i].row) continue;
		if (queen.col == state[i].col
			|| queen.row == state[i].row
			|| queen.row - queen.col == state[i].row - state[i].col
			|| queen.row + queen.col == state[i].row + state[i].col) {
			result++;
		}
	}
	return result;
}

int count(State& state) {
	int result = 0;
	for (int i = 0; i < state.size(); i++) {
		for (int j = i + 1; j < state.size(); j++) {
			if (state[j].col == state[i].col
				|| state[j].row == state[i].row
				|| state[j].row - state[j].col == state[i].row - state[i].col
				|| state[j].row + state[j].col == state[i].row + state[i].col) {
				result++;
			}
		}
	}
	return result;
}

Queen& get_queen(State& state) {
	int index = rand() % state.size();
	while (count(state[index], state) < 1) {
		index = rand() % state.size();
	}
	return state[index];
}

void queen_min_conflicts(Queen& queen, State& state, int& conf) {
	auto min_queen = queen;
	auto min_conflicts = count(state);
	auto found_min = false;
	for (int i = 0; i < state.size() && min_conflicts > 0; i++) {
		queen.row = i;
		auto conflicts = count(state);
		if (conflicts < min_conflicts) {
			min_conflicts = conflicts;
			min_queen = queen;
			found_min = true;
		}
	}

	queen.col = min_queen.col;
	if (!found_min) {
		min_queen.row = rand() % state.size();
		min_conflicts = count(state);
	}
	
	queen.row = min_queen.row;
	conf = min_conflicts;
}

void min_conflicts_discover(Queen& queen, State& processed, int n) {
	auto min_queen = queen;
	auto min_conflicts = count(queen, processed);
	bool found_min = false;

	if (min_conflicts == 0)return;
	for (int i = 0; i < n; i++) {
		queen.row = i;
		auto conflicts = count(queen, processed);
		if (conflicts < min_conflicts) {
			min_conflicts = conflicts;
			min_queen = queen;
			found_min = true;
		}

		if (min_conflicts == 0)return;
	}

	if (!found_min) {
		min_queen.row = rand() % n;
	}

	queen.col = min_queen.col;
	queen.row = min_queen.row;
}

State init(int n) {
	State state;
	state.reserve(n);
	for (int i = 0; i < n; i++) {
		state.push_back({ rand() % n, i });
	}
	return state;
}

State min_init(int n) {
	State state;
	state.reserve(n);
	for (int i = 0; i < n; i++) {
		Queen queen = { 0, i };
		min_conflicts_discover(queen, state, n);
		state.push_back(queen);
	}
	return state;
}


State min_conflicts(int n, int& steps) {
	auto state = min_init(n);
	auto conf = count(state);
	while (conf > 0) {
		auto& queen = get_queen(state);
		min_conflicts_discover(queen, state, n);
		conf = count(state);
		steps++;
	}
	return state;
}

//State min_conflicts(int n, int& steps) {
//	auto state = init(n);
//	auto conf = count(state);
//	while (conf > 0) {
//		queen_min_conflicts(get_queen(state), state, conf);
//		steps++;
//	}
//	return state;
//}

void print(State& state) {
	std::sort(state.begin(), state.end(), [](Queen& a, Queen& b) {
		return a.row < b.row;
	});

	for (int i = 0; i < state.size(); i++) {
		for (int j = 0; j < state.size(); j++) {
			if (state[i].col != j) std::cout << "- ";
			else std::cout << "* ";
		}
		std::cout << "\n";
	}
}

//int main() { 
//	srand(time(0));
//	bool solution;
//	auto t1 = clock();
//	int steps = 0;
//	auto result = min_conflicts(8, steps);
//	print(result);
//	std::cout << "Time: " << clock() - t1<<"ms\n";
//	return 0;
//}