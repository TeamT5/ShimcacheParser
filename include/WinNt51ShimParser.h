#ifndef _WINNT51SHIMPARSER_H_
#define _WINNT51SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: WinXP 32biy
class WinNt51ShimParser
	: public WinNtShimParser {
public:
	WinNt51ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	bool extractEntry(u_char *index);
protected:
	u_int numEntries;
	string terminal;
};

#endif