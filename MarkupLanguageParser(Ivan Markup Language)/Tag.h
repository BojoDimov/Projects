#pragma once
#include <vector>
#include <string>

class Tag
{
private:
	std::string _name;
	std::string _attribute;
	std::vector<double> _elements;
public:
	Tag(std::string name, std::string attr, std::vector<double> elements = *new std::vector<double>(0))
		:_name(name), _attribute(attr), _elements(elements) { }

	~Tag() { }

	virtual std::vector<double> apply() = 0;

	std::string getAttribute()const { return this->_attribute; }

	std:: vector<double> getData()const { return this->_elements; }

};

