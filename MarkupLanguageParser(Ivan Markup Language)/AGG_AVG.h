#pragma once
#include "Tag.h"

class AGG_AVG :public Tag
{
public:
	AGG_AVG(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~AGG_AVG() { }

	std::vector<double> apply() {
		std::vector<double> result(1);
		result[0] = 0;
		for (auto element : this->Tag::getData()) {
			result[0] += element;
		}
		result[0] /= this->Tag::getData().size();
		return result;
	}
};