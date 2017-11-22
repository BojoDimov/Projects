#pragma once
#include <exception>
#include <algorithm>
#include "Tag.h"

class SRT_ORD :public Tag
{
private:
	bool static asc_comparer(double a, double b) {
		return a < b;
	}
	bool static dsc_comparer(double a, double b) {
		return a > b;
	}
public:
	SRT_ORD(std::string name, std::string attr, std::vector<double> elements)
		:Tag(name, attr, elements) { }
	~SRT_ORD() { }

	std::vector<double> apply() {
		std::string attr = this->Tag::getAttribute();
		std::string ordertype = attr.substr(1, attr.size() - 2);
		std::vector<double> result = this->Tag::getData();
		if (ordertype == "ASC") {
			std::sort(result.begin(), result.end(), SRT_ORD::asc_comparer);
		}
		else if (ordertype == "DSC") {
			std::sort(result.begin(), result.end(), SRT_ORD::dsc_comparer);
		}
		else {
			throw std::exception("Attribute not supported!");
		}
		return result;
	}
};
