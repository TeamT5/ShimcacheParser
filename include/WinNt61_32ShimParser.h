#ifndef _WINNT61_32SHIMPARSER_H_
#define _WINNT61_32SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: win7_x86 win2008_R2_x86
class WinNt61_32ShimParser
	: public WinNtShimParser {
public:
	WinNt61_32ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	bool extractEntry(u_char *index);
protected:
	u_int numEntries;
};

#endif
