#pragma once
#include <vector>
#include <unordered_map>

#define INPUT "-i"
#define NODES "-n"
#define OUTPUT "-o"
#define THREADS "-t"
#define QUIET "-q"
#define TEST "--test"
#define AVGTEST "--test-avg"

struct BFSResult {
	int state;
	int level;
	int parent;
};

typedef std::vector<std::vector<int>> Graph;
typedef std::unordered_map<std::string, std::string> CLI;
typedef std::vector<BFSResult> BFS;