#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Helper.h"
using namespace std;

class Formatter
{
public:

	static vector<string> split_whitespace(string iml) {
		vector<string> result;
		string current;
		int start_pos = -1;
		for (int i = 0; i < iml.size(); i++) {
			if (start_pos == -1 && Helper::not_whitespace(iml[i])) {
				start_pos = i;
			}
			if (start_pos != -1 && !Helper::not_whitespace(iml[i])) {
				current = iml.substr(start_pos, i - start_pos);
				result.push_back(current);
				start_pos = -1;
			}
		}
		result.push_back(iml.substr(start_pos, iml.size() - start_pos));

		vector<string> _final;
		for (int i = 0; i < result.size(); i++) {
			string word = remove_parenthesis(result[i]);
			if (word != "") {
				_final.push_back(word);
			}
		}
		return _final;
	}

	static string remove_parenthesis(string item) {
		string result = "";
		for (auto c : item) {
			if (c != '<' && c != '>') {
				result += c;
			}
		}

		return result;
	}

	static int scanForClosingTag(vector<string> container, string tag, int start_pos, int end_pos) {
		stack<string> tags;
		tags.push(tag);
		start_pos++;
		for (int i = start_pos; i < end_pos; i++) {
			if (tags.top() == container[i].substr(1)) {
				tags.pop();
			}
			if (Helper::is_tag(container[i])) {
				tags.push(container[i]);
			}
			if (tags.size() == 0)return i;
		}
		return -1;
	}
	
	static string read_file(string source) {
		string result = "", current = "";
		fstream file;
		file.open(source, ios::in);
		file.seekg(0, ios::beg);
		while (getline(file, current)) {
			result += current;
		}
		file.close();
		return result;
	}

	static string format_input(string raw) {
		string result = "";
		char prev = raw[0];
		result += prev;
		for (int i = 1; i < raw.size(); i++) {
			char c = raw[i];
			if ((prev == '>'
				&& (isdigit(c) || c == '<'))
				|| (isdigit(prev) && c == '<')
				|| (prev == '"' && c == '>')) {

				result += ' ';
			}
			prev = c;
			if (c != '\r') {
				result += c;
			}
		}
		return result;
	}

	static void write_file(vector<double>& container, string filename) {
		fstream file;
		file.open(filename, ios::out | ios::trunc);
		file.seekg(0, ios::beg);
		for (auto num : container) {
			file << num << " ";
		}
		file.close();
	}
};

