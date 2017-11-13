#include <iostream>
#include <vector>
#include <string>
#include <queue>

/*
	sliding-blocks problem
*/

typedef std::vector<std::vector<int>> Board;

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

struct GameStep {
	GameStep* prev;
	Board board;
	std::string step;
	int g;
	int h;

	GameStep(GameStep* _prev, Board _board, std::string _step, int _g, int _h)
		: prev(_prev), board(_board), step(_step), g(_g), h(_h) { }

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

struct GameStepComparer {
	bool operator()(const GameStep* a, const GameStep* b)const {
		return a->h + a->g > b->h + b->g;
	}
};

struct TreeNode {
	GameStep* step;
	TreeNode* left;
	TreeNode* right;
};

struct GameTree {
	TreeNode* root;

	GameTree() :root(NULL) { }

	bool _insert(TreeNode *& node, GameStep* step) {
		if (node == NULL) {
			node = new TreeNode{ step, NULL, NULL };
			return true;
		}
		else if (step->board == node->step->board) return false;
		else if (GameStepComparer()(step, node->step)) return _insert(node->left, step);
		else return _insert(node->right, step);
	}

	bool insert(GameStep* step) {
		return _insert(root, step);
	}
};

void find_empty(const Board& board, int& i, int& j) {
	for (i = 0; i < board.size(); i++) {
		for (j = 0; j < board.size(); j++) {
			if (board[i][j] == 0) return;
		}
	}
}

typedef std::priority_queue<GameStep*, std::vector<GameStep*>, GameStepComparer> Queue;
void expand(GameStep* node, Queue& queue, GameTree& visited) {
	int i, j;
	find_empty(node->board, i, j);

	if (i > 0) {
		auto board = node->board;
		std::swap(board[i][j], board[i - 1][j]);
		auto step = new GameStep(node, board, "down", node->g + 1, h2(board));
		if (visited.insert(step)) queue.push(step);
	}

	if (i < node->board.size() - 1) {
		auto board = node->board;
		std::swap(board[i][j], board[i + 1][j]);
		auto step = new GameStep(node, board, "up", node->g + 1, h2(board));
		if (visited.insert(step)) queue.push(step);
	}

	if (j > 0) {
		auto board = node->board;
		std::swap(board[i][j], board[i][j - 1]);
		auto step = new GameStep(node, board, "right", node->g + 1, h2(board));
		if (visited.insert(step)) queue.push(step);
	}

	if (j < node->board.size() - 1) {
		auto board = node->board;
		std::swap(board[i][j], board[i][j + 1]);
		auto step = new GameStep(node, board, "left", node->g + 1, h2(board));
		if (visited.insert(step)) queue.push(step);
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

int task2() {
	Board board;
	Queue queue;
	GameTree visited;
	input(board);
	queue.push(new GameStep(NULL, board, "", 0, h2(board)));

	while (!queue.empty()) {
		auto node = queue.top();
		visited.insert(node);
		queue.pop();
		if (node->h == 0) return show_solution(node);

		expand(node, queue, visited);
	}

	std::cout << "\nThere is no solution\n";
	return 0;
}
