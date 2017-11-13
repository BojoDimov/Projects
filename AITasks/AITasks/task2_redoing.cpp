#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

typedef std::vector<std::vector<int>> Board;

void input(Board& board);
int h2(const Board& b);

struct GameStep {
	GameStep* prev;
	Board board;
	std::string step;
	int g;
	int h;

	GameStep(GameStep* _prev, Board _board, std::string _step, int _g, int _h)
		: prev(_prev), board(_board), step(_step), g(_g), h(_h) { }

	bool operator<(const GameStep& other)const {
		// not working due to implementation of std::set.find()
		/*if (*this == other) return false;
		else if (other.h + other.g == h + g) return &other < this;
		else return other.h + other.g < h + g;*/
		return other.h + other.g < h + g;
	}

	bool operator==(const GameStep& o)const {
		if (h != o.h) return false;
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board.size(); j++) {
				if (board[i][j] != o.board[i][j]) return false;
			}
		}
		return true;
	}
};

bool _compare_second = false;
bool _compare_second_hack = false;

struct equality_comparator {
	bool operator()(const GameStep& a, const GameStep& b)const {
		if (a == b) {
			_compare_second = true;
			return false; 
		}
		else {
			if (_compare_second) {
				_compare_second_hack = true;
				_compare_second = false;
				return true;
			}
			else {
				if (_compare_second_hack) {
					_compare_second_hack = false;
					return false;
				}
				else {
					// < compare
					if (a.g + a.h == b.g + b.h)
						return a.prev < b.prev;
					else return a.g + a.h < b.g + b.h;
				}
			}
		}
	}
};

void expand(GameStep* node , std::priority_queue<GameStep*>& queue, std::set<GameStep, equality_comparator>& visited);
int show_solution(GameStep* node);

int main() {
	Board board;
	std::priority_queue<GameStep*> queue;
	// it is working !!!
	std::set<GameStep, equality_comparator> visited;
	input(board);
	queue.push(new GameStep(NULL, board, "", 0, h2(board)));
	//visited.insert(GameStep(NULL, board, "", 0, h2(board)));
	//auto b1 = board;
	//std::swap(b1[2][0], b1[2][1]);
	//visited.insert(GameStep(NULL, b1, "", 0, h2(b1)));

	//auto wtf = visited.find(GameStep(NULL, board, "right", 2, h2(board)));

	while (!queue.empty()) {
		auto node = queue.top();
		visited.insert(*node);
		queue.pop();
		if (node->h == 0) return show_solution(node);
	
		expand(node, queue, visited);
	}

	std::cout << "\nThere is no solution\n";
	return 0;
}

void find_empty(const Board& board, int& i, int& j) {
	for (i = 0; i < board.size(); i++) {
		for (j = 0; j < board.size(); j++) {
			if (board[i][j] == 0) return;
		}
	}
}

void expand(GameStep* node, std::priority_queue<GameStep*>& queue, std::set<GameStep, equality_comparator>& visited) {
  	int i, j;
	find_empty(node->board, i, j);

	if (i > 0) {
		auto board = node->board;
		std::swap(board[i][j], board[i - 1][j]);
		auto step = new GameStep(node, board, "down", node->g + 1, h2(board));
		auto wtf = visited.find(*step);
		if(visited.find(*step) == visited.end()) queue.push(step);
	}

	if (i < node->board.size() - 1) {
		auto board = node->board;
		std::swap(board[i][j], board[i + 1][j]);
		auto step = new GameStep(node, board, "up", node->g + 1, h2(board));
		auto wtf = visited.find(*step);
		if (visited.find(*step) == visited.end()) queue.push(step);
	}

	if (j > 0) {
		auto board = node->board;
		std::swap(board[i][j], board[i][j - 1]);
		auto step = new GameStep(node, board, "right", node->g + 1, h2(board));
		auto wtf = visited.find(*step);
		if (visited.find(*step) == visited.end()) queue.push(step);
	}

	if (j < node->board.size() - 1) {
		auto board = node->board;
		std::swap(board[i][j], board[i][j + 1]);
		auto step = new GameStep(node, board, "left", node->g + 1, h2(board));
		auto wtf = visited.find(*step);
		if (visited.find(*step) == visited.end()) queue.push(step);
	}
}

int show_solution(GameStep* node) {
	std::vector<std::string> solution;
	auto current = node;
	while (current != NULL) {
		solution.push_back(current->step);
		current = current->prev;
	}
	solution.push_back(std::to_string(node->g));
	std::cout << "\n";
	for (int i = solution.size() - 1; i >= 0; i--) {
		std::cout << solution[i] << "\n";
	}
	return 0;
}

int h2(const Board& b) {
	int s = b.size();
	int sum = 0, pos_i, pos_j;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			if (b[i][j] != 0) {
				pos_i = (b[i][j] - 1) / s;
				pos_j = (b[i][j] - 1) % s;
				sum += abs(pos_i - i) + abs(pos_j - j);
			}
		}
	}
	return sum;
}

void input(Board& board) {
	int n;
	std::cin >> n;
	int board_size = sqrt(n + 1);
	for (int i = 0; i < board_size; i++) {
		board.push_back(std::vector<int>());
		for (int j = 0; j < board_size; j++) {
			std::cin >> n;
			board[i].push_back(n);
		}
	}
}