#ifndef _c15_h
#define _c15_h
#include <stdio.h>
#include <errno.h>
#include <string.h>
// statement expression

// Everything relate to METAPROGRAMMING DEBUGGING...  , need to use MACRO define
// inline function: simple, multi-used function 

// ^PO: print debug info
#ifdef NDEBUG     // If it's release version
#define _DEBUG(M, ...)   // dynamic amount of paras, at least 1
#else   // Output file name, error line, other changable variables
#define _DEBUG(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define _CLEAN_ERROR() (errno == 0 ? "None" : strerror(errno))

#define _LOG_ERR(M, ...) frpintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, _CLEAN_ERROR(), ##__VA_ARGS__)

#define _LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, _CLEAN_ERROR(), ##__VA_ARGS__)

#define _LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define _CHECK(A, M, ...) if(!(A)) { _LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error;}

#define _SENTINEL(M, ...) { _LOG_ERR(M, ##__VA_ARGS__); errno=0; goto error;}

#define _CHECK_MEM(A) _CHECK((A), "OUT OF MEMORY")

#define _CHECK_DEBUG(A, M, ...) if(!(A)) { _DEBUG(M, ##__VA_ARGS__); errno=0, goto error;}

#endif

