#ifndef _WINNT10SHIMPARSER_H_
#define _WINNT10SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: Win10
class WinNt10ShimParser
	: public WinNtShimParser {
public:
	WinNt10ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	virtual bool extractEntry(u_char* &index);
	bool extractEntryMeta(u_char* &index, u_int &entryLen);
protected:
	u_int magicValue;
	u_char statsSize;
};

#endif