#ifndef _WINNT60_64SHIMPARSER_H_
#define _WINNT60_64SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: Vista_x64 Win2008_x64 Win2003_x64
class WinNt60_64ShimParser
	: public WinNtShimParser {
public:
	WinNt60_64ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	bool extractEntry(u_char *index);
protected:
	u_int numEntries;
};

#endif