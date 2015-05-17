#include <iostream>
#include "..\..\Utils\Utils.h"
#include "..\TokenAnalisys.h"
#include "..\TextTypes.h"

using namespace std;
using namespace TEXTTOOLS;

void main()
{
	/***
	 * Sample 2:
	 *
	 * Individual token configuration.
	 * ----
	 */

TokenAnalysis
	ta;
TokenConfigStruct
	tc = TOKEN_CONFIG_DEFAULT;

	// Individual tokens configured as recurring.

	// 1º Sample: appellant parameter set to true.
	tc.appellant = true;

	ta.addToken(0, "-", tc);

string
	strSample = "a----bcd--ef-g";
StringListType
	sl;

	ta.breakString(strSample, sl);

	cout << "string decomposed using appellant == true.\n";
	for (StringListType::iterator it = sl.begin(); it != sl.end(); it++)
		cout << *it << "\n";

	// 2º Sample: appellant parameter set to false;
	tc.appellant = false;

	sl.clear();
	ta.setTokenConfig("-", tc);
	ta.breakString(strSample, sl);

	cout << "\nstring decomposed using appellant == false.\n";
	for (StringListType::iterator it = sl.begin(); it != sl.end(); it++)
		cout << *it << "\n";

	getchar();
};