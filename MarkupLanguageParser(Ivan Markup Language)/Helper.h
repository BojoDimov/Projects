#pragma once
#include <string>
using namespace std;

class Helper
{
public:
	static bool is_tag(string& item) {
		return item == "AGG-AVG"
			|| item == "AGG-FST"
			|| item == "AGG-LST"
			|| item == "AGG-PRO"
			|| item == "AGG-SUM"
			|| item == "MAP-INC"
			|| item == "MAP-MLT"
			|| item == "SRT-DST"
			|| item == "SRT-ORD"
			|| item == "SRT-REV"
			|| item == "SRT-SLC";
	}

	static bool is_number(string& item) {
		return item[0] == '-' || (item[0] >= '0' && item[0] <= '9');
	}

	static bool is_attribute(string& item) {
		if (item[0] == '\"') {
			if (item[item.size() - 1] == '\"') {
				return true;
			}
			else {
				throw exception("Invalid attribute syntax");
			}
		}
		else {
			return false;
		}
	}

	static bool not_whitespace(char a) {
		return a != '\t' && a != '\n' && a != ' ';
	}

	static void append(vector<double>& target, vector<double>& source) {
		for (auto number : source) {
			target.push_back(number);
		}
	}
};

