#include <iostream>
#include "..\TokenAnalisys.h"

using namespace std;
using namespace TEXTTOOLS;

void main()
{

TokenAnalysis
	ta;
StringListType
	sl;
string
	str = "String;breaking;test";

	cout << "string = " << str.c_str() << "\n\n";

	ta.addToken(0, ";");
	ta.breakString(str, sl);

	cout << "with separators:\n";

	for (StringListType::iterator it = sl.begin(); it != sl.end(); it++)
		cout << *it << "\n";

	cout << "\nno separators:\n";

	sl.clear();
	ta.breakString(str, sl, false);

	for (StringListType::iterator it = sl.begin(); it != sl.end(); it++)
		cout << *it << "\n";

	getchar();
};