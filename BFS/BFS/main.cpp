#include "utility.h"

//bool check_marked(std::vector<int>& m) {
//	for (int i = 0; i < m.size(); i++) {
//		if (m[i] == 0) {
//			std::cout << "Integrity is violated \n";
//			return false;
//		}
//	}
//}
//
//void print(const BFS& bfs) {
//	for (int i = 0; i < bfs.size(); i++) {
//		std::cout << "state:" << bfs[i].state << " level:" << bfs[i].level << " root:" << bfs[i].root << std::endl;
//	}
//}


//void test(int data_size, int max_thread_size) {
//	Logger Log("");
//	auto graph = generate(data_size);
//	//auto graph = generate_graph_from_file("input.txt");
//	int start;
//	for (int i = 1; i <= max_thread_size; i =i*2) {
//		start = clock();
//		bfs(graph, i);
//		Log("BFS " + std::to_string(i) + " threads finished for " + std::to_string(clock() - start) + "ms\n");
//	}
//}

int main(int argc, char** argv) {
	execute_commands(parse_commands(argc, argv));
	return 0;
}