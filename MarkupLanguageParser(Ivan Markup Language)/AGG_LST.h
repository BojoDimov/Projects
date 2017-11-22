#pragma once
#include "Tag.h"

class AGG_LST :public Tag
{
public:
	AGG_LST(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~AGG_LST() { }

	std::vector<double> apply() {
		std::vector<double> result;
		result.push_back(this->Tag::getData()[this->Tag::getData().size() - 1]);
		return result;
	}
};
