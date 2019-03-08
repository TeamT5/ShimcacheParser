#include "WinNt63ShimParser.h"
#include "ShimCacheInfo.h"

WinNt63ShimParser::WinNt63ShimParser() {
	this->magicValue = CACHE_MAGIC_NT6_3;
}