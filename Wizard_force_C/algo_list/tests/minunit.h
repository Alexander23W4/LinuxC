#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include "dbg.h"
#include <stdlib.h>

// 函数多、模块多、要写 持续集成/自动化测试，或者以后要做 单元测试报告，就保留 mu_* 框架。
// 它的核心价值是 自动记录哪些测试通过、失败原因、统计测试数量。

// MIN UNIT TEST MACRO FRAMEWORK
// with test framework, the test.c code could be CLEAN & TIDY, while output standard LOG INFO

#define mu_suite_start() char *message = NULL

// use as assert  (like in DBG MACRO, we use Assert())
#define mu_assert(test, message) if (!(test)) {\
log_err(message); return message; }

// execute function-test function 
#define mu_run_test(test) debug("\n-----%s", " " #test); \
message = test(); tests_run++; if (message) return message;


// this MACRO aims to decline boilerplate, the framework can be universally reused
// the framework could generate personal-standard LOG & use every test time (like DEBUG MACRO -> dbg.h)
#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
(void)argc; \
debug("----- RUNNING: %s", argv[0]);\
printf("----\nRUNNING: %s\n", argv[0]);\
char *result = name();\
if (result != 0) {\
printf("FAILED: %s\n", result);\
}\
else {\
printf("ALL TESTS PASSED\n");\
}\
printf("Tests run: %d\n", tests_run);\
exit(result != 0);\
}

int tests_run;

#endif













