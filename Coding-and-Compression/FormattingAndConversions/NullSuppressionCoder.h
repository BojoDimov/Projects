#pragma once
#include "SequenceCoder.h"
#include <vector>

const char CODING_SYMBOL = 27;
//encodes sequences of 5 or more 0 symbols
class NullSuppressionCoder :
	public SequenceCoder
{
public:
	NullSuppressionCoder(int treshold = 5):_treshold(treshold) { }
	~NullSuppressionCoder() { }

	std::vector<int> encode_sequence(const std::vector<int>&);

	std::vector<int> decode_sequence(const std::vector<int>&);

private:
	int _treshold;
};

