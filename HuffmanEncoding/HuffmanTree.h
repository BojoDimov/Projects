#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int occurances;
	int symbol;
	Node* left;
	Node* right;
	Node(int o, int s = -1) :occurances(o), symbol(s), left(nullptr), right(nullptr) {}
};

struct Char {
	char symbol;
	vector<bool> code;
	Char(char s, vector<bool> c):symbol(s),code(c){}

	void print() {
		cout << symbol << " - ";
		for (auto bit : code) {
			cout << bit;
		}
		cout << endl;
	}
};

struct Occurance {
	char symbol;
	int count;
	Occurance(char s = '\0') :count(1), symbol(s) {}
};

class HuffmanTree
{
private:
	Node* root;

	vector<Occurance> _frequency_table;

	void _print(Node* node);

	void _buildTree(vector<Occurance>& frequency_table);

	void _make_table(string text, vector<Occurance>& frequency_table);

	void _destroy(Node* node);

	void _add_to_alphabet_recursively(vector<bool> container, vector<Char>& alphabet, Node* node);
public:

	HuffmanTree(int o, int s = -1);

	HuffmanTree(string text);

	HuffmanTree(vector<Occurance>& frequency_table);

	~HuffmanTree();

	void print();

	void merge(HuffmanTree*&);

	bool operator>(HuffmanTree&);

	bool operator<(HuffmanTree&);

	vector<Char> make_alphabet();

	vector<unsigned char> compress(string text, int& totalCount);

	string decompress(vector<unsigned char> compressed_bits,int intsCount);

	vector<Occurance>& getTable();
};

