#include "WinNt51ShimParser.h"
#include "CacheEntryNt51.h"
#include "ShimCacheInfo.h"

WinNt51ShimParser::WinNt51ShimParser() {
	char temp[2] = { 0x00, 0x00 };
	this->terminal = string(temp, 2);
}

bool WinNt51ShimParser::parse(string &binData, vector<pair<wstring, wstring>> &result) {
	if (!this->initial(binData, result))
		return false;
	u_int num = 0x01;
	u_char *begin = (u_char*)this->mbinData.c_str();
	u_char *index = begin;
	index += CACHE_HEADER_SIZE_NT5_1;
	while ((size_t)(index - begin) <= binData.size() 
			&& num <= this->numEntries) {
		if (!this->extractEntry(index))
			break;
		index += NT5_1_ENTRY_SIZE;
		num++;
	}

	return true;
}

bool WinNt51ShimParser::initial(string &binData, vector<pair<wstring, wstring>> &result) {
	this->mbinData = binData;
	this->numEntries = *(u_int*)(binData.c_str() + 4);
	this->result = &result;
    this->result->resize(0);
	return true;
}

bool WinNt51ShimParser::extractEntry(u_char *index) {
	size_t end;
	CacheEntryNt51 entry;
	wstring wpath;
	string lastModDate;
	size_t found;
	size_t len = NT5_1_MAX_PATH32 + 4;
	end = (char*)index - this->mbinData.c_str() + NT5_1_ENTRY_SIZE;
	if (end > this->mbinData.size())
		return false; //overflow
	entry.Path = string((char*)index, (NT5_1_MAX_PATH32 + 4));
	found = entry.Path.find(this->terminal);
	if (found != std::string::npos) //find terminal index
		len = found + 1;
	wpath = wstring((wchar_t*)index, len/sizeof(wchar_t));
	//make file path
	this->filterPath(wpath);
	index = index + NT5_1_MAX_PATH32 + 4;
	entry.info = *(EntrySimpleNt51*)index;
	//make time
	lastModDate = this->makeTime(entry.info.ftLastModTime);
	//put to result
    this->putToResult(lastModDate, wpath);
	return true;
}
