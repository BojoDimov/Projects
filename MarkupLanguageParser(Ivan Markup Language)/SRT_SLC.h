#pragma once
#include <exception>
#include <algorithm>
#include <iostream>
#include <string>
#include "Tag.h"

class SRT_SLC :public Tag
{
public:
	SRT_SLC(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~SRT_SLC() { }

	std::vector<double> apply() {
		std::vector<double> result(0);
		std::string attr = this->Tag::getAttribute();
		double index = std::stod(attr.substr(1, attr.size() - 2));
		if (index < 0) {
			throw std::exception("Invalid index range");
		}
		std::vector<double> elements = this->Tag::getData();
		for (index; index < elements.size(); index++) {
			result.push_back(elements[index]);
		}
		return result;
	}
};