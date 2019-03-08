#ifndef _WINNT61_64SHIMPARSER_H_
#define _WINNT61_64SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: win7_x64 win2008_R2_x64
class WinNt61_64ShimParser 
	: public WinNtShimParser {
public:
	WinNt61_64ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	bool extractEntry(u_char *index);
protected:
	u_int numEntries;
};

#endif
