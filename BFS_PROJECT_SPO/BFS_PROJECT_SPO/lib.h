#pragma once
#include <ctime>
#include <thread>
#include <mutex>
#include "Logger.h"
#include "Timer.h"
#include "typedefs.h"

Graph generate_graph(int dim, double edge_prob = (double)1/5 ) {
	std::srand(std::time(0));
	int coff = 1 / edge_prob;
	Graph result(dim);
	for (int i = 0; i < dim; i++) {
		result[i] = std::vector<int>(dim);
		for (int j = 0; j < dim; j++) {
			if (std::rand() % coff == 0) {
				result[i][j] = 1;
			}
		}
	}
	return result;
}

int get_range(int start, int max, int granularity) {
	return std::min(max, start + granularity);
}

Graph generate_graph_parallel(int dim, int t, int granularity, double edge_prob = (double)1 / 5) {
	std::srand(std::time(0));
	int coff = 1 / edge_prob;
	Graph result(dim);
	std::vector<std::thread> thread_pool(t);
	int next_start = 0, next_stop;
	std::mutex next_state_mutex;

	for (int i = 0; i < t; i++) {
		thread_pool[i] = std::thread([&, i]() {
			while (next_start < dim) {
				next_state_mutex.lock();

				auto index = next_start;
				auto next_stop = get_range(index, dim, granularity);
				next_start = next_stop;

				next_state_mutex.unlock();

				for (index; index < next_stop; index++) {
					result[index] = std::vector<int>(dim);
					for (int j = 0; j < dim; j++) {
						if (std::rand() % coff == 0) {
							result[index][j] = 1;
						}
					}
				}
			}
		});
	}

	for (int i = 0; i < t; i++) {
		thread_pool[i].join();
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

BFS bfs(const Graph& g, int t, Logger& Log) {
	Timer timer;
	BFS states;
	states.reserve(g.size());
	std::vector<int> marked(g.size());
	std::vector<std::thread> tp(t);
	std::mutex mutex_n, mutex_states, mutex_marked;

	int n = 0;
	states.push_back({ 0 ,0 ,0 });
	marked[0] = true;

	timer.start();
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
								states.push_back({ i, states[index].level + 1, state });
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

	auto execution_time = timer.time();
	Log("Execution time is " + std::to_string(execution_time) + "ms\n");
	return states;
}

int get_next(std::vector<int>& marked, std::mutex& m) {
	for (int i = 0; i < marked.size(); i++) {
		m.lock();
		if (!marked[i]) {
			m.unlock();
			return i;
		}
		else{
			m.unlock();
		}
	}
}

BFS bfs2(const Graph& g, int t, Logger& Log) {
	Timer timer;
	BFS states;
	states.reserve(g.size());
	std::vector<int> marked(g.size());
	std::vector<std::thread> tp(t);
	std::mutex mutex_n, mutex_states, mutex_marked;

	int n = 0;
	states.push_back({ 0 ,0 ,0 });
	marked[0] = true;

	timer.start();
	for (int k = 0; k < t; k++) {
		tp[k] = std::thread([&, k]() {
			Log("Thread " + std::to_string(k) + " started\n");

			while (states.size() < g.size()) {
				
				mutex_n.lock();
				mutex_states.lock();
				int index = n;
				if (index == states.size()) {
					int next_state = get_next(marked, mutex_marked);
					states.push_back({ next_state, 0 , next_state });
					mutex_marked.lock();
					marked[next_state] = 1;
					mutex_marked.unlock();
				}
				auto state = states[index].state;
				n++;
				mutex_n.unlock();
				mutex_states.unlock();

				auto trn = g[state];

				for (int i = 0; i < g.size(); i++) {

					if (states.size() == g.size()) {
						return;
					}

					if (trn[i] && !marked[i]) {

						mutex_marked.lock();
						marked[i] = true;
						mutex_marked.unlock();

						mutex_states.lock();
						states.push_back({ i, states[index].level + 1, state });
						mutex_states.unlock();
					}
				}
			}

			Log("Thread " + std::to_string(k) + " finished\n");
		});
	}

	for (int k = 0; k < t; k++) {
		tp[k].join();
	}

	auto execution_time = timer.time();
	Log("Execution time is " + std::to_string(execution_time) + "ms\n");
	return states;
}