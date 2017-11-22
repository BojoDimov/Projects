#pragma once
#include "Tag.h"

class AGG_FST :public Tag
{
public:
	AGG_FST(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~AGG_FST() { }

	std::vector<double> apply() {
		std::vector<double> result;
		result.push_back(this->Tag::getData()[0]);
		return result;
	}
};
