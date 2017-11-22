#include "HelperService.h"
#include <bitset>
#include <iostream>


HelperService::HelperService()
{
}


HelperService::~HelperService()
{
}

std::vector<bool> HelperService::string_to_bits(const std::string& input)
{
	std::vector<bool> output;
	for (auto c : input) {
		std::bitset<8> bits(c);
		for (int i = 7; i >= 0; i--) {
			//bits are stored from back to front so i reverse traverse the array
			//this is only for display, in real life we dont need this
			output.push_back(bits[i]);
		}
	}
	return output;
}

void HelperService::print_bit_vector(const std::vector<bool>& input)
{
	int counter = 0;
	for (auto bit : input) {
		if (counter % 8 == 0 && counter != 0)
			std::cout << " ";
		std::cout << bit;
		counter++;
	}
}
