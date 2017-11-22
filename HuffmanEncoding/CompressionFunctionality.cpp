#include "CompressionFunctionality.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;


CompressionFunctionality::CompressionFunctionality()
{
}

CompressionFunctionality::~CompressionFunctionality()
{
}

void CompressionFunctionality::compress(string filename_in, string filename_out)
{
	//#region extract characters from binary file
	fstream file;
	file.open(filename_in, ios::in | ios::binary);
	file.seekg(0, ios::end);
	int filesize = file.tellg();
	file.seekg(0, ios::beg);
	char* bytestream = new char[filesize + 1];
	file.read(bytestream, filesize);
	string text(bytestream,filesize);
	delete bytestream;
	file.close();
	//#endregion

	//#region compress text
	HuffmanTree tree(text);
	vector<Occurance> table = tree.getTable();
	int bitsCount = 0;
	vector<unsigned char> compressed = tree.compress(text,bitsCount);
	//#endregion

	//#region write compressed text
	int text_size = compressed.size();
	int table_size = table.size();
	unsigned char* bytes = new unsigned char[text_size +1];
	for (int i = 0; i <text_size; i++) {
		bytes[i] = compressed[i];
	}
	file.open(filename_out, ios::out | ios::binary | ios::trunc);
	file.seekg(0, ios::beg);

	file.write((const char*)&bitsCount, sizeof(int));
	file.write((const char*)&table_size, sizeof(int));
	for (int i = 0; i < table.size(); i++) {
		file.write((const char*)&table[i], sizeof(Occurance));
	}
	file.write((const char*)bytes, text_size);
	file.close();
	//#endregion
}

void CompressionFunctionality::decompress(string filename_in, string filename_out)
{
	//#region extract compressed characters
	fstream file;
	file.open(filename_in, ios::in | ios::binary);
	file.seekg(0, ios::beg);
	int bitsCount = 0;
	int table_size;
	file.read((char*)&bitsCount, sizeof(int));
	file.read((char*)&table_size, sizeof(int));
	Occurance* table = new Occurance[table_size];
	file.read((char*)table, table_size*sizeof(Occurance));
	vector<Occurance> frequency_table;
	for (int i = 0; i < table_size; i++) {
		frequency_table.push_back(table[i]);
		cout << table[i].symbol << " - " << table[i].count << endl;
	}
	delete table;
	vector<unsigned char> compressed_bits;
	unsigned char symbol;
	while (!file.eof()) {
		file.read((char*)&symbol, sizeof(unsigned char));
		compressed_bits.push_back(symbol);
	}
	file.close();
	//#endregion

	//#region decompress
	HuffmanTree tree(frequency_table);
	string text = tree.decompress(compressed_bits, bitsCount);
	cout << endl << text << endl;
	//#endregion

	//#region write decompressed content
	file.open(filename_out, ios::out | ios::binary | ios::trunc);
	for (int i = 0; i < text.size(); i++) {
		file.write((const char*)&text[i], sizeof(char));
	}
	//#endregion
}

void CompressionFunctionality::parameters_parse(int argc, char ** argv)
{
	vector<string> arguments;
	for (int i = 0; i < argc; i++) {
		arguments.push_back(argv[i]);
	}
	bool is_in_compress_mode = false;
	bool seen_indentificator = false;
	string source = "", destination = "";

	
	for (int i = 0; i < arguments.size(); i++) {
		if (!seen_indentificator) {
			if (arguments[i] == "-c" || arguments[i] == "-compress") {
				is_in_compress_mode = true;
				seen_indentificator = true;
				continue;
			}
			if (arguments[i] == "-d" || arguments[i] == "-decompress") {
				is_in_compress_mode = false;
				seen_indentificator = true;
				continue;
			}
		}
		if (arguments[i] == "-i" && i < arguments.size() - 1) {
			if (i == arguments.size() - 1) {
				throw exception("Invalid arguments count!!!");
			}
			source = arguments[++i];
			continue;
		}
		if (arguments[i] == "-o" && i < arguments.size() - 1) {
			if (i == arguments.size() - 1) {
				throw exception("Invalid arguments count!!!");
			}
			destination = arguments[++i];
			continue;
		}
	}
	if (!seen_indentificator) {
		throw exception("invalid parameters:must specify type of operation or set default\n");
	}
	if (is_in_compress_mode) {
		this->compress(source, destination);
	}
	else {
		this->decompress(source, destination);
	}
}
