#ifndef _CACHEENTRYNT60_64_H_
#define _CACHEENTRYNT60_64_H_

#include "ShimCacheInfo.h"

using namespace std;

class CacheEntryNt60_64 {
public:
	void operator = (const CacheEntryNt60_64 &info) {
		this->wLength = info.wLength;
		this->wMaxLength = info.wMaxLength;
		this->dwPadding = info.dwPadding;
		this->dwPathOffset = info.dwPathOffset;
		this->ftLastModTime = info.ftLastModTime;
		this->dwInsertFlags = info.dwInsertFlags;
		this->dwShimFlags = info.dwShimFlags;
	}
public:
	u_short wLength;
	u_short wMaxLength;
	DWORD dwPadding;
	QWORD dwPathOffset;
	FILETIME  ftLastModTime;
	DWORD dwInsertFlags;
	DWORD dwShimFlags;
};

#endif
