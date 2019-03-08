#ifndef _CACHEENTRYNT61_64_H_
#define _CACHEENTRYNT61_64_H_

#include "ShimCacheInfo.h"

using namespace std;

class CacheEntryNt61_64 {
public:
	void operator = (const CacheEntryNt61_64 &info) {
		this->wLength = info.wLength;
		this->wMaxLength = info.wMaxLength;
		this->dwPadding = info.dwPadding;
		this->dwPathOffset = info.dwPathOffset;
		this->ftLastModTime = info.ftLastModTime;
		this->dwInsertFlags = info.dwInsertFlags;
		this->dwShimFlags = info.dwShimFlags;
		this->qwBlobSize = info.qwBlobSize;
		this->qeBlobOffset = info.qeBlobOffset;
	}
public:
	u_short wLength;
	u_short wMaxLength;
	DWORD dwPadding;
	QWORD dwPathOffset;
	FILETIME  ftLastModTime;
	DWORD dwInsertFlags;
	DWORD dwShimFlags;
	QWORD qwBlobSize;
	QWORD qeBlobOffset;
};

#endif
