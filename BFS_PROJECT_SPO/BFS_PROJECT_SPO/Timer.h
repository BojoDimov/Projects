#pragma once
#include <ctime>
#include <chrono>

class Timer
{
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
	//std::chrono::time_point<std::chrono::high_resolution_clock> root = std::chrono::high_resolution_clock::now();
public:
	void start() {
		_start = std::chrono::high_resolution_clock::now();
	}

	int time() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _start).count();
	}
};