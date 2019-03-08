# ShimcacheParser

A simple parser(library) which extracts shimcache data from windows.

### Supported OS
* Windows NT 5.1         (XP)
* Windows NT 5.2         (XP, 2003)
* Windows NT 6.0 x86/x64 (Vista, 2008)
* Windows NT 6.1 x86/X64 (7, 2008R2)
* Windows NT 6.2         (8, 2012)
* Windows NT 6.3         (8.1, 2012R2)
* Windows NT 10.0        (10, 2016)

### How to build

You can use the visual studio sln in project folder to build .exe or dynamic lib.


### How to use
*   Have a look on main.cpp to know usage of shimcache_parser.

*   Need to define SHIMCACHE_PARSER_DYNAMIC in the project, which includes shimcache parser

    , only if you want to include shimcache_parser as a dynamic library.

### Information about Shimcache
https://medium.com/@mbromileyDFIR/windows-wednesday-shim-cache-1997ba8b13e7

### Commercial use

If you want to use this parser and keep your code proprietary, please contact TeamT5.
