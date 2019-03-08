#ifndef _WINNTSHIMPARSER_H_
#define _WINNTSHIMPARSER_H_

#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

class WinNtShimParser {
public:
	WinNtShimParser();
	virtual bool parse(string &binData, vector<pair<wstring, wstring>> &result);  //need implementation
protected:
	virtual bool initial(string &binData, vector<pair<wstring, wstring>> &result); //need implementation
	virtual bool extractEntry(u_char *index); //need implementation
	virtual void filterPath(wstring &path);
	virtual string makeTime(FILETIME &ftime);
    virtual void putToResult(string &lastModDate, wstring &path);
protected:
	string mbinData;
	//json::value result;
    vector<pair<wstring, wstring>> *result;
};

#endif
