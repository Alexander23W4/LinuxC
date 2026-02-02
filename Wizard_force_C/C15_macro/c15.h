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

#define _LOG_ERR(M, ...) frpintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define _LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define _LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif

