#include "BitMaskCoder.h"
#include <iostream>
const char CODING_SYMBOL = 0;

void BitMaskCoder::handle_non_aligned_input(std::bitset<8>& mask, int current_pos, int max_pos) {
	int pos_difference = max_pos - current_pos;
	if (pos_difference > 0 && pos_difference < 8) {
		for (int i = 7 - pos_difference; i >= 0; i--) {
			mask[i] = 1;
		}
	}
}

std::vector<int> BitMaskCoder::encode_sequence(const std::vector<int>& input)
{
	std::vector<int> output;
	std::bitset<8> current_mask;
	int current_mask_pos;
	int size = input.size();
	for (int i = 0; i < size; i++) {
		output.push_back(0);
		current_mask.reset();
		current_mask_pos = output.size() - 1;
		handle_non_aligned_input(current_mask, i, size);
		for (int j = 7; j >= 0 && i < size; j--, i++) {
			current_mask[j] = input[i] != CODING_SYMBOL;
			if (input[i] != CODING_SYMBOL) {
				output.push_back(input[i]);
			}
		}
		i--;
		output[current_mask_pos] = current_mask.to_ulong();
	}
	return output;
}

std::vector<int> BitMaskCoder::decode_sequence(const std::vector<int>& input)
{
	std::vector<int> output;
	for (int i = 0; i < input.size(); i++) {
		std::bitset<8> mask(input[i]);
		for (int j = 7; j >= 0 && i < input.size() - 1; j--) {
			if (mask[j] == 0) {
				output.push_back(CODING_SYMBOL);
			}else{
				output.push_back(input[++i]);
			}
		}
	}
	return output;
}
