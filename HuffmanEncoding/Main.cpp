#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include "HuffmanTree.h"
#include "CompressionFunctionality.h"
using namespace std;

void test_compress_decompress() {
	HuffmanTree tree("ABRACADABRA");
	int count = 0;
	std::vector<unsigned char> result = tree.compress("ABRACADABRAABRA", count);
	cout << "Symbols decompressed = " << count << endl;
	for (auto c : result) {
		cout << c << "  ";
	}
	string yolo = tree.decompress(result, count);
	cout << "\n" << yolo << endl;
}

int main(int argc, char **argv) 
{
	CompressionFunctionality compressor;
	compressor.parameters_parse(argc, argv);
	//compressor.compress("original_text.txt", "compressed.txt");
	//compressor.decompress("compressed.txt", "decompressed_text.txt");
	//test_compress_decompress();
	return 0;
}