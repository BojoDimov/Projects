#include "utility.h"

int main(int argc, char** argv) {
	execute_commands(parse_commands(argc, argv));
	//auto g = generate_graph_parallel(10, 1, 2,1);
	return 0;
}