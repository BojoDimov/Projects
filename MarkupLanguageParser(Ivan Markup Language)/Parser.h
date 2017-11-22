#pragma once
#include "Helper.h"
#include "Formatter.h"
#include <exception>
using namespace std;
class Tag;

class Parser
{
private:
	 static vector<double> _parse(vector<string>& container, int start_pos, int end_pos) {
		vector<double> result;
		for (int i = start_pos; i < end_pos; i++) {
			if (Helper::is_number(container[i])) {
				result.push_back(parse_number(container[i]));
			}
			if (Helper::is_tag(container[i])) {
				int closingTag = Formatter::scanForClosingTag(container, container[i], i, end_pos);
				if (closingTag > 0) {
					try {
						Tag* element = factory(container, i, closingTag);
						Helper::append(result, element->apply());
						i = closingTag;
					}
					catch (exception e) {
						cout << "Invalid tag name" << endl;
					}
					
				}
				else {
					throw exception("Closing tag not found");
				}
			}
		}
		return result;
	}
public:
	static double parse_number(string& item) {
		return stod(item);
	}

	static string parse_attr(string& item) {
		string parsed = item.substr(1, item.size() - 2);
		return parsed;
	}

	static Tag* factory(vector<string>& container, int start_pos, int end_pos) {
		string attribute = "";
		string tag_name = container[start_pos];
		start_pos++;
		try {
			if (Helper::is_attribute(container[start_pos])) {
				attribute = container[start_pos];
				start_pos++;
			}
		}
		catch (exception e) {
			cout << "Invalid attribute syntax";
		}
		
		vector<double> items = _parse(container, start_pos, end_pos);
		Tag* element;

		if (tag_name == "MAP-INC") {
			element = new MAP_INC(tag_name, attribute, items);
		}
		else if (tag_name == "MAP-MLT") {
			element = new MAP_MLT(tag_name, attribute, items);
		}
		else if (tag_name == "AGG-SUM") {
			element = new AGG_SUM(tag_name, attribute, items);
		}
		else if (tag_name == "AGG-PRO") {
			element = new AGG_PRO(tag_name, attribute, items);
		}
		else if (tag_name == "AGG-AVG") {
			element = new AGG_AVG(tag_name, attribute, items);
		}
		else if (tag_name == "AGG-FST") {
			element = new AGG_FST(tag_name, attribute, items);
		}
		else if (tag_name == "AGG_LST") {
			element = new AGG_LST(tag_name, attribute, items);
		}
		else if (tag_name == "SRT-REV") {
			element = new SRT_REV(tag_name, attribute, items);
		}
		else if (tag_name == "SRT-ORD") {
			element = new SRT_ORD(tag_name, attribute, items);
		}
		else if (tag_name == "SRT-SLC") {
			element = new SRT_SLC(tag_name, attribute, items);
		}
		else if (tag_name == "SRT-DST") {
			element = new SRT_DST(tag_name, attribute, items);
		}
		else {
			throw exception("Invalid syntax - unsupportd tagname\n");
		}

		return element;
	}

	static void parse(string input, string output) {
		vector<string> words = 
			Formatter::split_whitespace(
				Formatter::format_input(
					Formatter::read_file(input)));
		try {
			vector<double> evaluated = _parse(words, 0, words.size());
			Formatter::write_file(evaluated, output);
		}
		catch (exception e) {
			cout << "Markup parsing error"<< endl;
		}
	}
};

