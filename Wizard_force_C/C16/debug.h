/*----------------------------------------------------------------------------------
HEAD FIEL  debug.h    Wang
2026.2.2
The file is particularly debugging oriented macro definition focus. 
 ----------------------------------------------------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#ifdef NDEBUG
#define _DEBUG(M, ...) 
#else
#define _DEBUG(M, ...) frpintf(stderr, "[DEBUG] (%s, %d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define _CLEAR_ERROR() (errno ? strerror(errno) : "NONE")
#define _LOG_ERR(M, ...) fprintf(stderr, "[ERROR] (%s, %d): %s " M "\n", __FILE__, __LINE__, _CLEAR_ERROR(), ##__VA_ARGS__)
#define _LOG_WARN(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, _CLEAN_ERROR(), ##__VA_ARGS__)
#define _LOG_INFO(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// the parenthesis is always essiential in Head File
#define _CHECK(A, M, ...)  \
if(!(A)){ \
    _LOG_ERR(M, ##__VA_ARGS__); \
    errno=0; \
    goto error; \
}

#define _SENTINEL(M, ...) \
{  \
    _LOG_ERR(M, ##__VA_ARGS__); \
    errno=0; \
    goto error;  \
}


#endif
