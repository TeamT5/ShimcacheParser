#include "WinNt10CShimParser.h"
#include "ShimCacheInfo.h"

WinNt10CShimParser::WinNt10CShimParser() {
	this->magicValue = CACHE_MAGIC_NT10;
	this->statsSize = NT10_CREATORS_STATS_SIZE;
}