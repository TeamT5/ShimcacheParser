#ifndef _WINNT60_32SHIMPARSER_H_
#define _WINNT60_32SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: Vista_x86 Win2008_x86 Win2003_x86
class WinNt60_32ShimParser
	: public WinNtShimParser {
public:
	WinNt60_32ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	bool extractEntry(u_char *index);
protected:
	u_int numEntries;
};

#endif