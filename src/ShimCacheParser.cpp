#include "ShimCacheParser.h"
#include "ShimCacheInfo.h"
#include "WinNT10CShimParser.h"
#include "WinNT10ShimParser.h"
#include "WinNt63ShimParser.h"
#include "WinNt62ShimParser.h"
#include "WinNt61_64ShimParser.h"
#include "WinNt61_32ShimParser.h"
#include "WinNt60_64ShimParser.h"
#include "WinNt60_32ShimParser.h"
#include "WinNt51ShimParser.h"

ShimCacheParser::ShimCacheParser() {
	//initial all OS parser
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT10, shared_ptr<WinNtShimParser>(new WinNt10ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT10C, shared_ptr<WinNtShimParser>(new WinNt10CShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT63, shared_ptr<WinNtShimParser>(new WinNt63ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT62, shared_ptr<WinNtShimParser>(new WinNt62ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT61_64, shared_ptr<WinNtShimParser>(new WinNt61_64ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT61_32, shared_ptr<WinNtShimParser>(new WinNt61_32ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT60_64, shared_ptr<WinNtShimParser>(new WinNt60_64ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT60_32, shared_ptr<WinNtShimParser>(new WinNt60_32ShimParser())));
	this->parserPool.insert(pair<OSversion, shared_ptr<WinNtShimParser>>
		(OSversion::NT51, shared_ptr<WinNtShimParser>(new WinNt51ShimParser())));
}

bool ShimCacheParser::parse(string &binData, vector<pair<wstring, wstring>> &result) {
	this->mbinData = binData;
	this->result = &result;
    this->result->resize(0);
	OSversion version = this->checkOS();
	if (version != OSversion::unknown) 
	{
		this->dispatch(version);
		return true;
	}
	return false;
}

OSversion ShimCacheParser::checkOS() 
{
	u_char *index = (u_char*)this->mbinData.c_str();
	u_int *magic = NULL;
	size_t end = sizeof(u_int);
	if (end > this->mbinData.size())
		return OSversion::unknown;
	magic = (u_int*)index;
	if (*magic == CACHE_MAGIC_NT6_1)
		return this->checkNT61_32_64();
	//windows 5.2 is the same as windows 6.0
	if (*magic == CACHE_MAGIC_NT6_0)
		return this->checkNT60_32_64();
	if (*magic == CACHE_MAGIC_NT5_1)
		return OSversion::NT51;
	end = NT6_2_STATS_SIZE + sizeof(u_int);
	if (end > this->mbinData.size())
		return OSversion::unknown;
	magic = (u_int*)(index + NT6_2_STATS_SIZE);
	if (*magic == CACHE_MAGIC_NT6_3)
		return OSversion::NT63;
	if (*magic == CACHE_MAGIC_NT6_2)
		return OSversion::NT62;
	end = NT10_STATS_SIZE + sizeof(u_int);
	if (end > this->mbinData.size())
		return OSversion::unknown;
	magic = (u_int*)(index + NT10_STATS_SIZE);
	if (*magic == CACHE_MAGIC_NT10)
		return OSversion::NT10;
	end = NT10_CREATORS_STATS_SIZE + sizeof(u_int);
	if (end > this->mbinData.size())
		return OSversion::unknown;
	magic = (u_int*)(index + NT10_CREATORS_STATS_SIZE);
	if (*magic == CACHE_MAGIC_NT10)
		return OSversion::NT10C;
	return OSversion::unknown;
}

OSversion ShimCacheParser::checkNT61_32_64() {
	//end = header bytes size + length bytes size + maxlength bytes size + padding bytes size
	size_t end = CACHE_HEADER_SIZE_NT6_1 + sizeof(u_short) * 2 + sizeof(u_int);
	if (end > this->mbinData.size())
		return OSversion::unknown;
	u_char *index = (u_char*)(this->mbinData.c_str() + CACHE_HEADER_SIZE_NT6_1);
	u_short *length = (u_short*)index; //2 bytes
	u_short *maxlength = (u_short*)(index + 2); //2 bytes
	u_int *padding = (u_int*)(index + 4); //4 bytes
	if ((*maxlength - *length) == NT6_1_SUB_LEN) {
		if (*padding == 0x00000000)
			return OSversion::NT61_64;
		else
			return OSversion::NT61_32;
	}
	return OSversion::unknown;
}

OSversion ShimCacheParser::checkNT60_32_64() 
{
	//end = header bytes size + length bytes size + maxlength bytes size + padding bytes size
	size_t end = CACHE_HEADER_SIZE_NT6_0 + sizeof(u_short) * 2 + sizeof(u_int);
	if (end > this->mbinData.size())
		return OSversion::unknown;
	u_char *index = (u_char*)(this->mbinData.c_str() + CACHE_HEADER_SIZE_NT6_0);
	u_short *length = (u_short*)index; //2 bytes
	u_short *maxlength = (u_short*)(index + 2); //2 bytes
	u_int *padding = (u_int*)(index + 4); //4 bytes
	if ((*maxlength - *length) == NT6_0_SUB_LEN) {
		if (*padding == 0x00000000)
			return OSversion::NT60_64;
		else
			return OSversion::NT60_32;
	}
	return OSversion::unknown;
}

void ShimCacheParser::dispatch(OSversion version) {
	shared_ptr<WinNtShimParser> ptr;
	ptr = this->parserPool[version];
	ptr->parse(this->mbinData, *this->result);
}