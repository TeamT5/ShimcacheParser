#ifndef _SHIMCACHEPARSERCONF_H_
#define _SHIMCACHEPARSERCONF_H_

# ifdef SHIMCACHE_PARSER_DYNAMIC
    #ifdef SHIMCACHE_PARSER_BUILD_DLL
        #define SHIMCACHE_PREFIX __declspec(dllexport)
    #else
        #define SHIMCACHE_PREFIX __declspec(dllimport)
#endif
# else
    #define SHIMCACHE_PREFIX
# endif

#endif
