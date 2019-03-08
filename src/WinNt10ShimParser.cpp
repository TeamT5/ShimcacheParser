#include "WinNt10ShimParser.h"
#include "ShimCacheInfo.h"

WinNt10ShimParser::WinNt10ShimParser() {
	this->magicValue = CACHE_MAGIC_NT10;
	this->statsSize = NT10_STATS_SIZE;
}

bool WinNt10ShimParser::parse(string &binData, vector<pair<wstring, wstring>> &result) {
	if (!this->initial(binData, result))
		return false;
	u_char *begin = (u_char*)this->mbinData.c_str();
	u_char *index = begin;
	index += this->statsSize; //skip stats info
	while ((size_t)(index - begin) <= this->mbinData.size()) {
		if (!this->extractEntry(index))
			break;
	}

	return true;
}

bool WinNt10ShimParser::initial(string &binData, vector<pair<wstring, wstring>> &result) {
	this->mbinData = binData;
	this->result = &result;
    this->result->resize(0);
	return true;
}

bool WinNt10ShimParser::extractEntry(u_char* &index) {
	u_int entryLen;
	size_t end;
	u_char* curIndex; //using for extracting data
	FILETIME ftime;
	u_short pathLen;
	wstring wpath = L"None";
	string lastModDate;
	if (!this->extractEntryMeta(index, entryLen))
		return false;
	end = ((char*)(index + entryLen) - this->mbinData.c_str());
	if (end > this->mbinData.size())
		return false; //overflow
	curIndex = index;
	index += entryLen; //move index to next entry
	//extract path
	pathLen = *(u_short*)curIndex;
	curIndex += 2;
	// check path len is 0 or not
	if (pathLen != 0)
		wpath = wstring((wchar_t*)curIndex, pathLen/sizeof(wchar_t));
	curIndex += pathLen;
	//rest data
	end = (char*)curIndex - this->mbinData.c_str() + NT10_REST_LEN;
	if (end > this->mbinData.size())
		return false; //overflow
	ftime = *(FILETIME*)(curIndex);
	curIndex += NT10_REST_LEN;
	//make time
	lastModDate = this->makeTime(ftime);
	//put to result
    this->putToResult(lastModDate, wpath);
	return true;
}

bool WinNt10ShimParser::extractEntryMeta(u_char* &index, u_int &entryLen) {
	size_t end = (char*)index - this->mbinData.c_str() + NT10_ENTRY_META_LEN;
	if (end > this->mbinData.size())
		return false; //overflow
	if (*(u_int*)index != this->magicValue)
		return false; //invalid version
	entryLen = *(u_int*)(index + 8);
	index += NT10_ENTRY_META_LEN;
	return true;
}

