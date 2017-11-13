#pragma once
#include <ctime>
#include <thread>
#include <mutex>
#include "Logger.h"
#include "typedefs.h"

Graph generate_graph(int dim) {
	std::srand(std::time(0));

	Graph result(dim);
	for (int i = 0; i < dim; i++) {
		result[i] = std::vector<int>(dim);
		for (int j = 0; j < dim; j++) {
			if (std::rand() % 5 == 0) {
				result[i][j] = 1;
			}
		}
	}
	return result;
}

Graph generate_graph_from_file(std::string file) {
	std::fstream input(file);
	std::string line;
	std::getline(input, line);
	int dim = std::stoi(line);
	Graph graph(dim);
	for (int i = 0; i < dim; i++) {
		std::getline(input, line);
		for (int k = 0; k < line.size(); k++) {
			if (line[k] == '1') {
				graph[i].push_back(1);
			}

			if (line[k] == '0') {
				graph[i].push_back(0);
			}
		}
	}

	return graph;
}

BFS bfs(const Graph& g, int t, Logger& Log = Logger("")) {
	auto start_timer = std::clock();
	BFS states;
	states.reserve(g.size());
	std::vector<int> marked(g.size());
	std::vector<std::thread> tp(t);
	std::mutex mutex_n, mutex_states, mutex_marked;

	int n = 0;
	states.push_back({ 0 ,0 ,0 });
	marked[0] = true;

	for (int k = 0; k < t; k++) {
		tp[k] = std::thread([&, k]() {
			Log("Thread " + std::to_string(k) + " started\n");
			while (states.size() < g.size()) {
				while (n < states.size()) {
					mutex_n.lock();
					mutex_states.lock();

					int index = n;
					auto state = states[index].state;

					mutex_n.unlock();
					mutex_states.unlock();

					auto trn = g[state];


					for (int i = 0; i < g.size(); i++) {

						if (trn[i] && !marked[i]) {

							mutex_marked.lock();
							marked[i] = true;
							mutex_marked.unlock();

							if (states.size() < g.size()) {
								mutex_states.lock();
								states.push_back({ i, states[index].level + 1, states[index].root });
								mutex_states.unlock();
							}
						}
					}

					mutex_n.lock();
					n++;
					mutex_n.unlock();
				}

				for (int i = 0; i < g.size(); i++) {
					if (!marked[i]) {

						if (states.size() < g.size()) {
							mutex_states.lock();
							states.push_back({ i, 0, i });
							mutex_states.unlock();

							marked[i] = true;
							break;
						}
					}
				}
			}

			Log("Thread " + std::to_string(k) + " finished\n");
		});

	}

	for (int k = 0; k < t; k++) {
		tp[k].join();
	}

	auto execution_time = std::clock() - start_timer;
	Log("Execution time is " + std::to_string(execution_time) + "ms\n");
	return states;
}