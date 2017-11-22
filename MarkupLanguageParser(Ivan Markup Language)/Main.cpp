#include <iostream>
#include <stack>
#include "MAP_INC.h"
#include "MAP_MLT.h"
#include "AGG_SUM.h"
#include "AGG_PRO.h"
#include "AGG_AVG.h"
#include "AGG_FST.h"
#include "AGG_LST.h"
#include "SRT_REV.h"
#include "SRT_ORD.h"
#include "SRT_SLC.h"
#include "SRT_DST.h"
#include "Parser.h"
using namespace std;

int main() {
	string input, output;
	cout << "Enter input file name:";
	getline(cin, input);
	cout << "Enter input file name:";
	getline(cin, output);
	Parser::parse(input, output);
	return 0;
}