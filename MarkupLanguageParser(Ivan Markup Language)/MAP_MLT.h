#pragma once
#include "Tag.h"
#include <string>

class MAP_MLT :public Tag
{
public:
	MAP_MLT(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~MAP_MLT() { }

	std::vector<double> apply() {
		std::string attr = this->Tag::getAttribute();
		double mlt = std::stod(attr.substr(1, attr.size() - 2));
		std::vector<double> result;
		for (auto element : this->Tag::getData()) {
			result.push_back(element * mlt);
		}
		return result;
	}
};