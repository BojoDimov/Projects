#pragma once
#include<string>
#include "HuffmanTree.h"

using namespace std;

class CompressionFunctionality
{
public:
	CompressionFunctionality();
	~CompressionFunctionality();

	void compress(string filename_in, string filename_out);

	void decompress(string filename_in, string filename_out);

	void parameters_parse(int argc, char** argv);
};

