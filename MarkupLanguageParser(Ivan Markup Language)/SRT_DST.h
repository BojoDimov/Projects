#pragma once
#include <exception>
#include <algorithm>
#include <iostream>
#include "Tag.h"

class SRT_DST :public Tag
{
	template<typename T>
	bool static contains(std::vector<T> elements, T item ) {
		for (auto element : elements) {
			if (element == item) {
				return true;
			}
		}
		return false;
	}

public:
	SRT_DST(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~SRT_DST() { }

	std::vector<double> apply() {
		std::vector<double> result(0);
		std::vector<double> elements = this->Tag::getData();
		for (auto element:elements) {
			if (!SRT_DST::contains(result, element)) {
				result.push_back(element);
			}
		}
		return result;
	}
};
