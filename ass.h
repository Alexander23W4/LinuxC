#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#ifdef NDEBUG
#define _DEBUG(M, ...)
#else 
#define _DEBUG(M, ...) fprintf(stderr, "[DEBUG] FILE: %s, LINE: %d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define _OUT_ERR() (errno ? strerror(errno) : "NONE")

#define _LOG_ERR(M, ...) fprintf(stderr, "...", __FILE__, __LINE__, _OUT_ERR(), ##__VA_ARGS__)