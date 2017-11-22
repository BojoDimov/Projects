#pragma once
#include <vector>
class SequenceCoder
{
public:

	SequenceCoder()
	{
	}

	virtual std::vector<int> encode_sequence(const std::vector<int>& input) = 0;

	virtual std::vector<int> decode_sequence(const std::vector<int>& input) = 0;

	virtual ~SequenceCoder()
	{
	}
};

