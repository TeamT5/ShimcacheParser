#ifndef _SHIMCACHEPARSER_H_
#define _SHIMCACHEPARSER_H_

#include <string>
#include <memory>
#include <map>
#include "ShimCacheParserConf.h"
#include "WinNtShimParser.h"

using namespace std;

enum class OSversion {
	unknown,
	NT10,
	NT10C,
	NT63,
	NT62,
	NT61_64,
	NT61_32,
	NT60_64,
	NT60_32,
	NT51
};

class SHIMCACHE_PREFIX ShimCacheParser {
public:
	ShimCacheParser();
	~ShimCacheParser() = default;
	bool parse(string &binData, vector<pair<wstring, wstring>> &result);
private:
	OSversion checkOS();
	OSversion checkNT61_32_64();
	OSversion checkNT60_32_64();
	void dispatch(OSversion version);
private:
	string mbinData;
	map<OSversion, shared_ptr<WinNtShimParser>> parserPool;
    vector<pair<wstring, wstring>> *result;
};

#endif
