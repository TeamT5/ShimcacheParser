#ifndef _SHIMCACHEINFO_H_
#define _SHIMCACHEINFO_H_

#include <windows.h>

typedef unsigned __int64 QWORD;

const int timeBufSize = 20;

// Values used by Windows 10.0 (Win10)
const u_int CACHE_MAGIC_NT10 = 0x73743031;
const u_char NT10_STATS_SIZE = 0x30;
const int NT10_ENTRY_META_LEN = 12;
const int NT10_REST_LEN = 8;
const u_char NT10_CREATORS_STATS_SIZE = 0x34;

// Values used by Windows 6.3 (Win8.1)
const u_int CACHE_MAGIC_NT6_3 = 0x73743031;
const u_char NT6_3_STATS_SIZE = 0x80;
const int NT6_3_ENTRY_META_LEN = 12;

// Values used by Windows 6.2 (Win8)
const u_int CACHE_MAGIC_NT6_2 = 0x73743030;
const u_char NT6_2_STATS_SIZE = NT6_3_STATS_SIZE;
const int NT6_2_ENTRY_META_LEN = NT6_3_ENTRY_META_LEN;
const int NT_6_2_PACKAGE_LEN = 2;
const int NT_6_2_REST_LEN = 20;

// Values used by Windows 6.1 (Win7 and Server 2008 R2)
const u_int CACHE_MAGIC_NT6_1 = 0xbadc0fee;
const u_char CACHE_HEADER_SIZE_NT6_1 = 0x80;
const u_char NT6_1_ENTRY_SIZE32 = 0x20;
const u_char NT6_1_ENTRY_SIZE64 = 0x30;
const u_char CSRSS_FLAG = 0x2;
const u_char NT6_1_SUB_LEN = 0x2;

// Values used by Windows 6.0 (Vista and Server 2008)
// Values used by Windows 5.2 (Server 2003 and WinXP 64bit)
const u_int CACHE_MAGIC_NT6_0 = 0xbadc0ffe;
const u_char CACHE_HEADER_SIZE_NT6_0 = 0x08;
const u_char NT6_0_ENTRY_SIZE32 = 0x18;
const u_char NT6_0_ENTRY_SIZE64 = 0x20;
const u_char NT6_0_SUB_LEN = 0x2;

// Values used by Windows 5.1 (WinXP 32bit)
const u_int CACHE_MAGIC_NT5_1 = 0xdeadbeef;
const u_short CACHE_HEADER_SIZE_NT5_1 = 0x190;
const u_short NT5_1_ENTRY_SIZE = 0x228;
const int NT5_1_MAX_PATH32 = 524;

#endif // !_SHIMCACHEINFO_H

