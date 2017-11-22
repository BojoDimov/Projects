#pragma once
#include "Tag.h"
#include <string>

class MAP_INC:public Tag
{
public:
	MAP_INC(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~MAP_INC() { }

	std::vector<double> apply() {
		std::string attr = this->Tag::getAttribute();
		double inc = std::stod(attr.substr(1, attr.size() - 2));
		std::vector<double> result;
		for (auto element : this->Tag::getData()) {
			result.push_back(element + inc);
		}
		return result;
	}
};

