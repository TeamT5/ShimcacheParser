#ifndef _CACHEENTRYNT61_32_H_
#define _CACHEENTRYNT61_32_H_

#include "ShimCacheInfo.h"

using namespace std;

class CacheEntryNt61_32 {
public:
	void operator = (const CacheEntryNt61_32 &info) {
		this->wLength = info.wLength;
		this->wMaxLength = info.wMaxLength;
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
	DWORD dwPathOffset;
	FILETIME  ftLastModTime;
	DWORD dwInsertFlags;
	DWORD dwShimFlags;
	DWORD qwBlobSize;
	DWORD qeBlobOffset;
};

#endif
