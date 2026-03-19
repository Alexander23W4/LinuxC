#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <dbg.h>
#include <stdlib.h>

// MIN UNIT TEST MACRO FRAMEWORK
// with test framework, the test.c code could be CLEAN & TIDY, while output standard LOG INFO

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) {\
log_err(message); return message; }

#define mu_run_test(test) debug("\n-----%s", " " #test); \
message = test(); tests_run++; if (message) return message;


// this MACRO aims to decline boilerplate, the framework can be universally reused
// the framework could generate personal-standard LOG & use every test time (like DEBUG MACRO -> dbg.h)
#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
argc = 1; \
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