#pragma once
#include "SequenceCoder.h"
#include <vector>
#include <bitset>

class BitMaskCoder :
	public SequenceCoder
{
public:
	BitMaskCoder() { }
	~BitMaskCoder() { }

	std::vector<int> encode_sequence(const std::vector<int>&);

	std::vector<int> decode_sequence(const std::vector<int>&);

private:
	void handle_non_aligned_input(std::bitset<8>&, int, int);
};

