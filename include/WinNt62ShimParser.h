#ifndef _WINNT62SHIMPARSER_H_
#define _WINNT62SHIMPARSER_H_

#include "WinNtShimParser.h"
#include <string>

using namespace std;

//OS: Win8
class WinNt62ShimParser
	: public WinNtShimParser {
public:
	WinNt62ShimParser();
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
protected:
	bool initial(string &binData, vector<pair<wstring, wstring>> &result);
	virtual bool extractEntry(u_char* &index);
	bool extractEntryMeta(u_char* &index, u_int &entryLen);
	bool jumpPackage(u_char* &index);
protected:
	u_int magicValue;
};

#endif