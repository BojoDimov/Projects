#pragma once
#include "lib.h"


void dump_graph(Logger& Log, const BFS& bfs) {
	for (int i = 0; i < bfs.size(); i++) {
		Log(bfs[i]);
	}
}

CLI parse_commands(int argc, char** argv) {
	CLI result;
	for (int i = 0; i < argc; i++) {
		if (std::string(argv[i]) == INPUT || std::string(argv[i]) == "-input") {
			result[INPUT] = std::string(argv[++i]);
		}
		else if (std::string(argv[i]) == NODES) {
			result[NODES] = std::string(argv[++i]);
		}
		else if (std::string(argv[i]) == THREADS || std::string(argv[i]) == "-tasks") {
			result[THREADS] = std::string(argv[++i]);
		}
		else if (std::string(argv[i]) == OUTPUT || std::string(argv[i]) == "-output") {
			result[OUTPUT] = std::string(argv[++i]);
		}
		else if (std::string(argv[i]) == QUIET || std::string(argv[i]) == "-quiet") {
			result[QUIET] = "";
		}
	}
	return result;
}

void execute_commands(CLI commands) {
	Graph graph;
	Logger Log("");
	int thread_number = 1;
	BFS result;
	auto exec_start = std::clock();
	if (commands.find(QUIET) != commands.end()) {
		Log.quiet = true;
	}

	if (commands.find(INPUT) != commands.end()) {
		graph = generate_graph_from_file(commands[INPUT]);
	}
	else if (commands.find(NODES) != commands.end()) {
		graph = generate_graph(std::stoi(commands[NODES]));
	}
	else {
		Log("not sufficient commands\nTerminating...\n");
		return;
	}

	if (commands.find(THREADS) != commands.end()) {
		thread_number = std::stoi(commands[THREADS]);
	}

	result = bfs(graph, thread_number);

	if (commands.find(OUTPUT) != commands.end()) {
		dump_graph(Logger(commands[OUTPUT]), result);
	}

	auto execution_time = std::clock() - exec_start;
	Log("Total execution time is " + std::to_string(execution_time) + "ms\n");
}