#include "WinNt62ShimParser.h"
#include "ShimCacheInfo.h"

WinNt62ShimParser::WinNt62ShimParser() {
	this->magicValue = CACHE_MAGIC_NT6_2;
}

bool WinNt62ShimParser::parse(string &binData, vector<pair<wstring, wstring>> &result) {
	if (!this->initial(binData, result))
		return false;
	u_char *begin = (u_char*)this->mbinData.c_str();
	u_char *index = begin;
	index += NT6_2_STATS_SIZE; //skip stats info
	while ((size_t)(index - begin) <= this->mbinData.size()) {
		if (!this->extractEntry(index))
			break;
	}

	return true;
}

bool WinNt62ShimParser::initial(string &binData, vector<pair<wstring, wstring>> &result) {
	this->mbinData = binData;
	this->result = &result;
    this->result->resize(0);
	return true;
}

bool WinNt62ShimParser::extractEntry(u_char* &index) {
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
		wpath = wstring((wchar_t*)curIndex, pathLen / sizeof(wchar_t));
	curIndex += pathLen;
	//jump index to ingore package data
	if (!this->jumpPackage(curIndex))
		return false;
	//rest data
	end = (char*)curIndex - this->mbinData.c_str() + NT_6_2_REST_LEN;
	if (end > this->mbinData.size())
		return false; //overflow
	ftime.dwLowDateTime = *(DWORD*)(curIndex + 8);
	ftime.dwHighDateTime = *(DWORD*)(curIndex + 12);
	curIndex += NT_6_2_REST_LEN;
	//make time
	lastModDate = this->makeTime(ftime);
	//put to result
    this->putToResult(lastModDate, wpath);
	return true;
}

bool WinNt62ShimParser::extractEntryMeta(u_char* &index, u_int &entryLen) {
	size_t end = (char*)index - this->mbinData.c_str() + NT6_2_ENTRY_META_LEN;
	if (end > this->mbinData.size())
		return false; //overflow
	u_int temp = *(u_int*)index;
	if (*(u_int*)index != this->magicValue)
		return false; //invalid version
	entryLen = *(u_int*)(index + 8);
	index += NT6_2_ENTRY_META_LEN;
	return true;
}

bool WinNt62ShimParser::jumpPackage(u_char* &index) {
	size_t end = (char*)index - this->mbinData.c_str() + NT_6_2_PACKAGE_LEN;
	if(end > this->mbinData.size())
		return false; //overflow
	u_short packLen = *(u_short*)index;
	index += NT_6_2_PACKAGE_LEN;
	if (packLen != 0x0000) {
		end = (char*)index - this->mbinData.c_str() + packLen;
		if (end >= this->mbinData.size())
			return false; //overflow
		index += packLen;
	}
	return true;
}
