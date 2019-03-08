#include "WinNt61_32ShimParser.h"
#include "CacheEntryNt61_32.h"
#include "ShimCacheInfo.h"

WinNt61_32ShimParser::WinNt61_32ShimParser() {

}

bool WinNt61_32ShimParser::parse(string &binData, vector<pair<wstring, wstring>> &result) {
	if (!this->initial(binData, result))
		return false;
	u_int num = 0x01;
	u_char *begin = (u_char*)this->mbinData.c_str();
	u_char *index = begin;
	index += CACHE_HEADER_SIZE_NT6_1;
	while ((size_t)(index - begin)<binData.size() && num <= this->numEntries) {
		if (!this->extractEntry(index))
			break;
		index += NT6_1_ENTRY_SIZE32;
		num++;
	}

	return true;
}

bool WinNt61_32ShimParser::initial(string &binData, vector<pair<wstring, wstring>> &result) {
	this->mbinData = binData;
	this->numEntries = *(u_int*)(binData.c_str() + 4);
	this->result = &result;
    this->result->resize(0);
	return true;
}

bool WinNt61_32ShimParser::extractEntry(u_char *index) {
	CacheEntryNt61_32 entry;
	wstring wpath;
	string lastModDate;
	size_t end;
	end = (char*)index - this->mbinData.c_str() + NT6_1_ENTRY_SIZE32;
	if (end > this->mbinData.size())
		return false; //overflow
	entry = *(CacheEntryNt61_32*)index;
	//make file path
	wpath = wstring((wchar_t*)(this->mbinData.c_str() + entry.dwPathOffset)
		, entry.wLength / sizeof(wchar_t));
	this->filterPath(wpath);
	//make time
	lastModDate = this->makeTime(entry.ftLastModTime);
	//put to result
    this->putToResult(lastModDate, wpath);
	return true;
}