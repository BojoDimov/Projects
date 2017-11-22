#include <iostream>
#include <string>
#include <vector>
#include "NullSuppressionCoder.h"
#include "BitMaskCoder.h"
#include "HelperService.h"
using namespace std;


int main() {
	vector<int> test;
	int temp;
	for (int i = 0; i < 10; i++) {
		cin >> temp;
		test.push_back(temp);
	}

	SequenceCoder* coder = new BitMaskCoder();

	for (auto n : coder->decode_sequence(coder->encode_sequence(test))) {
		cout << n << " ";

	}
	/*for (auto n : coder->encode_sequence(test)) {
		cout << n << " ";
	}*/
	return 0;
}