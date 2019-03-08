#include "WinNtShimParser.h"
#include "ShimCacheInfo.h"
#include <algorithm>
#include <time.h>

WinNtShimParser::WinNtShimParser() 
{
}

bool WinNtShimParser::parse(string &binData, vector<pair<wstring, wstring>> &result) {
	//inherit class need implementation
	return 0;
}

bool WinNtShimParser::initial(string &binData, vector<pair<wstring, wstring>> &result) {
	//inherit class need implementation
	return true;
}

bool WinNtShimParser::extractEntry(u_char *index) {
	//inherit class need implementation
	return true;
}

void WinNtShimParser::filterPath(wstring &path) {
	path.erase(remove(path.begin(), path.end(), 0x0), path.end());
	size_t found = path.find(L"\\??\\");
	if (found != string::npos)
		path = path.substr(found + 4, path.length() - 4);
}

string WinNtShimParser::makeTime(FILETIME &ftime) 
{
	string timeStr = "N/A";
	struct tm tm_date;
	SYSTEMTIME tempTime;
	try 
	{
		if (ftime.dwHighDateTime != 0 && ftime.dwLowDateTime != 0) 
		{
			if (FileTimeToSystemTime(&ftime, &tempTime))
			{
				tm_date.tm_hour = tempTime.wHour;
				tm_date.tm_min = tempTime.wMinute;
				tm_date.tm_mday = tempTime.wDay;
				tm_date.tm_mon = tempTime.wMonth - 1;
				tm_date.tm_sec = tempTime.wSecond;
				tm_date.tm_year = tempTime.wYear - 1900;
				//date range check.
				if (0 <= tm_date.tm_hour  && tm_date.tm_hour <= 23 &&
					0 <= tm_date.tm_min   && tm_date.tm_min  <= 59 &&
					1 <= tm_date.tm_mday  && tm_date.tm_mday <= 31 &&
					0 <= tm_date.tm_mon   && tm_date.tm_mon  <= 11 &&
					0 <= tm_date.tm_sec   && tm_date.tm_sec  <= 59 &&
					0 <= tm_date.tm_year  && tm_date.tm_year <= 300)
				{
					char buffer[timeBufSize];
					strftime(buffer, timeBufSize, "%Y-%m-%d %H:%M:%S", &tm_date);
					timeStr = string(buffer);
				}
			}

		}
	}
	catch (...) 
	{
		timeStr = "N/A";
	}
	return timeStr;
}

void WinNtShimParser::putToResult(string &lastModDate, wstring &path) {
    setlocale(LC_CTYPE, "");
    size_t len = lastModDate.size() + 1;
    wchar_t *p = new wchar_t[len];
    size_t outSize;
    mbstowcs_s(&outSize, p, len, lastModDate.c_str(), len - 1);
    auto wlastModDate = wstring(p);
    delete[] p;
    this->result->push_back(pair<wstring, wstring>(wlastModDate, path));
}