#pragma once
#include <algorithm>
#include "lib.h"



//program crashes when the graph does not have edges-- this may be hint to what to change in order to work properly
//bfs2 is out and hasnt crashed yet

void dump_graph(Logger& Log, BFS bfs) {
	std::sort(bfs.begin(), bfs.end(), [](const BFSResult& a, const BFSResult& b) {
		return a.state < b.state;
	});

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
		else if (std::string(argv[i]) == TEST) {
			result[TEST] = "";
		}
		else if (std::string(argv[i]) == AVGTEST) {
			result[AVGTEST] = "";
		}
	}
	return result;
}


void test(int test_size, int max_thread, std::string output) {
	Logger Log(output);
	Logger intercept("");
	Timer timer;
	intercept.quiet = true;

	for (int threads = 1; threads <= max_thread; threads++) {
		timer.start();
		generate_graph_parallel(test_size, threads, 30);
		Log("Threads: " + std::to_string(threads) + " Execution time: " + std::to_string(timer.time()) + "ms\n");
	}
}

//void test_average(int test_size, int max_thread, std::string output) {
//	Logger Log(output);
//	Logger intercept("");
//	Timer timer;
//	intercept.quiet = true;
//
//	Graph g = generate_graph_parallel(test_size, max_thread);
//
//	for (int threads = 1; threads <= max_thread; threads++) {
//		timer.start();
//		bfs2(g, threads, intercept);
//		Log("Threads: " + std::to_string(threads) + " Execution time: " + std::to_string(timer.time()) + "ms\n");
//	}
//}

//void test(int test_size, int max_thread, std::string output) {
//	Logger Log(output);
//	Logger intercept("");
//	Timer timer;
//	intercept.quiet = true;
//
//	timer.start();
//	Graph graph = generate_graph(test_size);
//	auto graph_duration = timer.time();
//
//	for (int threads = 1; threads <= max_thread; threads++) {
//		timer.start();
//		bfs(graph, threads, intercept);
//		Log("Threads: " + std::to_string(threads) + " Execution time: " + std::to_string(timer.time()) + "ms\n");
//		Log("Total time: " + std::to_string(timer.time() + graph_duration) + "ms\n\n");
//	}
//}

void test_average(int test_size, int max_thread, std::string output, std::vector<double> probs) {
	int n = probs.size();
	std::vector<int> times(max_thread + 1);
	std::vector<int> total_time(max_thread + 1);
	Logger Log(output);
	Logger intercept("");
	Timer timer;
	intercept.quiet = true;
	

	for (int test_num = 0; test_num < n; test_num++) {
		timer.start();
		Graph graph = generate_graph(test_size, probs[test_num]);
		auto graph_duration = timer.time();

		for (int threads = 1; threads <= max_thread; threads++) {
			timer.start();
			bfs2(graph, threads, intercept);
			times[threads] += timer.time();
			total_time[threads] += timer.time() + graph_duration;
		}
	}

	for (int threads = 1; threads <= max_thread; threads++) {
		Log("Threads: " + std::to_string(threads) + " Average Execution time: " + std::to_string(times[threads] / n) + "ms\n");
		Log("Average Total time: " + std::to_string(total_time[threads] / n) + "ms\n\n");
	}
}

void test_average_p(int test_size, int max_thread, std::string output, std::vector<double> probs) {
	int n = probs.size();
	std::vector<int> times(max_thread + 1);
	std::vector<int> total_time(max_thread + 1);
	Logger Log(output);
	Logger intercept("");
	Timer timer;
	intercept.quiet = true;


	for (int test_num = 0; test_num < n; test_num++) {
		for (int threads = 1; threads <= max_thread; threads++) {
			timer.start();
			Graph graph = generate_graph_parallel(test_size, threads, 30, probs[test_num]);
			auto graph_duration = timer.time();
			bfs2(graph, threads, intercept);
			times[threads] += timer.time();
			total_time[threads] += timer.time() + graph_duration;
		}
	}

	for (int threads = 1; threads <= max_thread; threads++) {
		Log("Threads: " + std::to_string(threads) + " Average Execution time: " + std::to_string(times[threads] / n) + "ms\n");
		Log("Average Total time: " + std::to_string(total_time[threads] / n) + "ms\n\n");
	}
}

void execute_commands(CLI commands) {
	Graph graph;
	Logger Log("");
	int thread_number = 1;
	BFS result;
	Timer timer;
	timer.start();

	if (commands.find(TEST) != commands.end()) {
		test(std::stoi(commands[NODES]), std::stoi(commands[THREADS]), commands[OUTPUT]);
		return;
	}

	if (commands.find(AVGTEST) != commands.end()) {
		test_average_p(std::stoi(commands[NODES]), std::stoi(commands[THREADS]), commands[OUTPUT], { 0.2 , 0.1, 0.05, 0.01});
		//test_average(std::stoi(commands[NODES]), std::stoi(commands[THREADS]), commands[OUTPUT]);
		return;
	}


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

	result = bfs2(graph, thread_number, Log);

	if (commands.find(OUTPUT) != commands.end()) {
		Logger l(commands[OUTPUT]);
		dump_graph(l, result);
	}

	auto execution_time = timer.time();
	Log("Total execution time is " + std::to_string(execution_time) + "ms\n");
}