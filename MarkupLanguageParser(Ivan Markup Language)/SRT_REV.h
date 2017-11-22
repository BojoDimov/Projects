#pragma once
#include "Tag.h"

class SRT_REV :public Tag
{
public:
	SRT_REV(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~SRT_REV() { }

	std::vector<double> apply() {
		std::vector<double> result;
		std::vector<double> elements = this->Tag::getData();
		int size = elements.size();
		for (int i = elements.size() - 1 ; i >= 0; i--) {
			result.push_back(elements[i]);
		}
		return result;
	}
};
