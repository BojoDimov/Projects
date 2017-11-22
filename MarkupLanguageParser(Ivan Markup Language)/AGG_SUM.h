#pragma once
#include "Tag.h"

class AGG_SUM :public Tag
{
public:
	AGG_SUM(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~AGG_SUM() { }

	std::vector<double> apply() {
		std::vector<double> result(1);
		result[0] = 0;
		for (auto element : this->Tag::getData()) {
			result[0] += element;
		}
		return result;
	}
};
