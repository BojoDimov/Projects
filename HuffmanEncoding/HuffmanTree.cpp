/*
	@How we gonna represent the compressed files
	0. we must indicate somehow if this file is compressed using our technique
	1. first part is the occurance table length
	2. second part is the occurance table
	3. compressed in form of 8-bit blocks information
*/

#include "HuffmanTree.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <bitset>
#include <fstream>
using namespace std;


//#region Helper Functions
Char find_symbol(vector<Char> alphabet, char symbol) {
	for (auto c : alphabet) {
		if (symbol == c.symbol) {
			return c;
		}
	}
	throw new exception("Symbol not found - possible tree corruption!!!");
}

vector<unsigned char> make_ints(vector<bool> compressed_bits) {
	vector<unsigned char> ints(0);
	bitset<8> current;
	unsigned char test = 0;
	for (int i = 0; i < compressed_bits.size(); i++) {
		current[7 - i % 8] = compressed_bits[i];
		if ((i + 1) % 8 == 0) {
			ints.push_back(current.to_ulong());
		}
		else {
			test = test << 1;
		}
		if (i + 1 == compressed_bits.size()) {
			ints.push_back(current.to_ulong());
		}
	}
	return ints;
}

bool is_visited(vector<Node*> container, Node* node) {
	for (int i = 0; i < container.size(); i++) {
		if (container[i] == node) {
			return true;
		}
	}
	return false;
}

bool compare_trees(HuffmanTree* a, HuffmanTree* b) {
	return *a > *b;
}

//#endregion Helper Functions



void HuffmanTree::_print(Node * node)
{
	if (node != nullptr) {
		if (node->symbol > -1) {
			cout << (char)node->symbol << " - ";
		}
		cout << node->occurances << endl;
		_print(node->left);
		_print(node->right);
	}
}

void HuffmanTree::_buildTree(vector<Occurance>& frequency_table)
{
	this->_frequency_table = frequency_table;
	vector<HuffmanTree* > trees;
	for (int i = 0; i < frequency_table.size(); i++) {
		trees.push_back(new HuffmanTree(frequency_table[i].count, frequency_table[i].symbol));
	}
	while (trees.size() > 1) {
		sort(trees.begin(), trees.end(), compare_trees);
		trees[trees.size() - 2]->merge(trees[trees.size() - 1]);
		trees.pop_back();
	}
	this->root = trees[0]->root;
}

void HuffmanTree::_make_table(string text, vector<Occurance>& frequency_table)
{
	for (auto c : text) {
		bool alreadyOccured = false;
		for (int i = 0; i < frequency_table.size(); i++) {
			if (frequency_table[i].symbol == c) {
				frequency_table[i].count++;
				alreadyOccured = true;
				break;
			}
		}
		if (!alreadyOccured) {
			frequency_table.push_back(*new Occurance(c));
		}
	}
}

void HuffmanTree::_destroy(Node * node)
{
	if (node != nullptr) {
		_destroy(node->left);
		_destroy(node->right);
		delete node;
	}
}

HuffmanTree::HuffmanTree(string text) :root(NULL)
{
	vector<Occurance> frequency_table;
	this->_make_table(text, frequency_table);
	this->_buildTree(frequency_table);
}

HuffmanTree::HuffmanTree(vector<Occurance>& frequency_table)
{
	this->_buildTree(frequency_table);
}

HuffmanTree::HuffmanTree(int o, int s):root(new Node(o,s))
{
}

HuffmanTree::~HuffmanTree()
{
	_destroy(root);
}

void HuffmanTree::print()
{
	_print(root);
}

void HuffmanTree::merge(HuffmanTree *& other)
{
	Node* new_root = new Node(root->occurances + other->root->occurances);
	new_root->left = this->root;
	new_root->right = other->root;
	other = nullptr;
	this->root = new_root;
}

bool HuffmanTree::operator>(HuffmanTree & other)
{
	return this->root->occurances > other.root->occurances;
}

bool HuffmanTree::operator<(HuffmanTree & other)
{
	return this->root->occurances < other.root->occurances;
}

void add_to_alphabet_recursively(vector<bool> container, vector<Char>& alphabet, Node* node) {
	int temp_size = container.size();
	if (node->symbol > -1) {
		alphabet.push_back(*new Char(node->symbol, container));
		container.pop_back();
		return;
	}
	if (node->left) {
		container.push_back(false);
		add_to_alphabet_recursively(container, alphabet, node->left);
		container.pop_back();
	}
	if (node->right) {
		container.push_back(true);
		add_to_alphabet_recursively(container, alphabet, node->right);
		container.pop_back();
	}
}

vector<Char> HuffmanTree::make_alphabet()
{
	vector<Char> alphabet;
	vector<bool> current_bitset(0);

	add_to_alphabet_recursively(current_bitset, alphabet, this->root);

	return alphabet;
}

vector<unsigned char> HuffmanTree::compress(string text, int& totalCount)
{
	vector<Char> alphabet = this->make_alphabet();
	vector<bool> compressed(0);
	for (auto c : text) {
		Char current = find_symbol(alphabet, c);
		for (auto bit : current.code) {
			compressed.push_back(bit);
		}
	}
	totalCount = compressed.size();
	vector<unsigned char> result =  make_ints(compressed);
	return result;
}

string HuffmanTree::decompress(vector<unsigned char> ints, int bitsCount)
{
	string text = "";
	vector<bool> compressed_bits(0);
	bitset<8>* bits;
	int count = 0;
	for (auto c : ints) {
		bits = new bitset<8>(c);
		for (int i = 7; i >= 0 && count < bitsCount; i--) {
			compressed_bits.push_back((*bits)[i]);
			count++;
		}
		delete bits;
	}

	Node* it = this->root;
	for (auto bit : compressed_bits) {
		if (bit) {
			it = it->right;
		}
		else {
			it = it->left;
		}
		if (it->symbol > -1) {
			text += (char)it->symbol;
			it = this->root;
		}
	}
	return text;
}

vector<Occurance>& HuffmanTree::getTable()
{
	return this->_frequency_table;
}

