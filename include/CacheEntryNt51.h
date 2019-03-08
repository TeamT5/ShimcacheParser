#ifndef _CACHEENTRYNT51_H_
#define _CACHEENTRYNT51_H_

#include "ShimCacheInfo.h"
#include <string>

using namespace std;

//for easy assign byte value
class EntrySimpleNt51 {
public:
	void operator = (const EntrySimpleNt51 &info) {
		this->ftLastModTime = info.ftLastModTime;
		this->dwFileSize = info.dwFileSize;
		this->dwLowFileHigh = info.dwLowFileHigh;
		this->ftLastUpdateTime = info.ftLastUpdateTime;
	}
public:
	FILETIME  ftLastModTime;
	DWORD dwFileSize;
	DWORD dwLowFileHigh;
	FILETIME ftLastUpdateTime;
};

class CacheEntryNt51 {
public:
	//string is easier handling than wchar
	//But need to care of the size is NT5_1_MAX_PATH32 + 4
	string Path; 
	EntrySimpleNt51 info;
};

#endif
