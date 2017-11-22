#pragma once
#include "Tag.h"

class AGG_PRO :public Tag
{
public:
	AGG_PRO(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~AGG_PRO() { }

	std::vector<double> apply() {
		std::vector<double> result(1);
		result[0] = 1;
		for (auto element : this->Tag::getData()) {
			result[0] *= element;
		}
		return result;
	}
};