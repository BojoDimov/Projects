#pragma once
#include <string>
#include <vector>
static class HelperService
{
public:
	HelperService();
	~HelperService();

	static std::vector<bool> string_to_bits(const std::string&);

	static void print_bit_vector(const std::vector<bool>&);
};

