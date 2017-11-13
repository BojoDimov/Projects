#pragma once
#include <fstream>
#include <ostream>
#include <string>
#include <iostream>

#include "typedefs.h"

class Logger {
private:
	std::ofstream output;
	std::mutex m_log;
public:
	bool quiet;

	Logger(std::string o = "")
	{

		if (o == "") {
			quiet = false;
		}
		else {
			output = std::ofstream(o);
			quiet = true;
		}
	}

	Logger(const Logger& o) {
		quiet = o.quiet;
	}

	Logger& operator()(const std::string text) {
		if (quiet) {
			output << text;
		}
		else {
			//std::cout << text;
			printf("%s", text.c_str());
		}

		return *this;
	}

	Logger& operator()(int number) {
		if (quiet) {
			output << number;
		}
		else {
			//std::cout << number;
			printf("%i", number);
		}

		return *this;
	}

	void operator()(const BFSResult& res) {
		if (quiet) {
			output << "state:" << res.state << " level:" << res.level << " root:" << res.root << std::endl;
		}
		else {
			std::cout << "state:" << res.state << " level:" << res.level << " root:" << res.root << std::endl;
		}
	}
};