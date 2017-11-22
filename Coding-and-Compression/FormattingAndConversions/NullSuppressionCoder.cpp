#include "NullSuppressionCoder.h"
#include <iostream>


std::vector<int> NullSuppressionCoder::encode_sequence(const std::vector<int>& input)
{
	std::vector<int> output;
	int counter = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == 0) {
			counter++;

			if (i == input.size() - 1) {
				output.push_back(CODING_SYMBOL);
				output.push_back(counter);
			}
		}

		else {
			if (counter >= 0 && counter < _treshold) {
				for (int j = 1; j <= counter; j++) {
					output.push_back(0);
				}
			}
			else {
				output.push_back(CODING_SYMBOL);
				output.push_back(counter);
			}

			output.push_back(input[i]);
			counter = 0;
		}
	}

	std::cout << "compression rate - " << (double)input.size() / (double)output.size() << "\n";
	return output;
}

std::vector<int> NullSuppressionCoder::decode_sequence(const std::vector<int>& input)
{
	std::vector<int> output;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == CODING_SYMBOL) {
			for (int j = 1; j <= input[i + 1]; j++) {
				output.push_back(0);
			}
			i += 1;
		}
		else {
			output.push_back(input[i]);
		}
	}
	return output;
}
