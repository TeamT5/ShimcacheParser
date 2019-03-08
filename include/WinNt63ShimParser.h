#ifndef _WINNT63SHIMPARSER_H_
#define _WINNT63SHIMPARSER_H_

#include "WinNt62ShimParser.h"
#include <string>

using namespace std;

//OS: Win8.1
class WinNt63ShimParser
	: public WinNt62ShimParser {
public:
	WinNt63ShimParser();
};

#endif