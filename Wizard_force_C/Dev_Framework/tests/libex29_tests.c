#include "minunit.h"
#include <dlfcn.h>

// lib function type
typedef int (*lib_function) (const char *data);
typedef int (*lib_function_ext) (const char* data, int n);
char *lib_file = "build/lib29.so";
void *lib = NULL;


//-------------------check function common framework----------------------------
// ***!!!: these way to write check function is waste, I should think of MACRO representation instead momentarily
int check_function(const char *func_to_run, const char *data, int expected)
{
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL,
        "Did not find %s function in the library %s: %s", func_to_run,
        lib_file, dlerror());

    int rc = func(data);
    check(rc == expected, "Function %s return %d for data: %s",
        func_to_run, rc, data);

    return 1;
error:
    return 0;
}

int check_function_ext(const char* func_to_run, const char* data, int n, int expected){
    lib_function_ext func = dlsym(lib, func_to_run);
    check(func != NULL,
        "Did not find %s function in the library %s: %s", func_to_run,
        lib_file, dlerror());

    int rc = func(data, n);
    check(rc == expected, "Function %s return %d for data: %s",
        func_to_run, rc, data);

    return 1;
error:
    return 0;
}

// -------------------function-specific test functions------------------------

char *test_dlopen()
{
    lib = dlopen(lib_file, RTLD_NOW);
    mu_assert(lib != NULL, "Failed to open the library to test.");

    return NULL;
}

char *test_functions()
{
    mu_assert(check_function("print_a_message", "Hello", 0),
        "print_a_message failed.");
    mu_assert(check_function("uppercase", "Hello", 0),
        "uppercase failed.");
    mu_assert(check_function("lowercase", "Hello", 0),
        "lowercase failed.");

    return NULL;
}

// char *test_failures()
// {
//     mu_assert(check_function("fail_on_purpose", "Hello", 1),
//         "fail_on_purpose should fail.");

//     return NULL;
// }

char* test__print_msg(){
    mu_assert(check_function_ext("_print_msg", "Fucku", 3, 0),\
        "_print_msg failed.");
    return NULL;
}

char *test_dlclose()
{
    int rc = dlclose(lib);
    mu_assert(rc == 0, "Failed to close lib.");

    return NULL;
}

// ----------------------------------------------------------------------------

char *all_tests()  // all-batch test
{
    mu_suite_start();

    mu_run_test(test_dlopen);
    mu_run_test(test_functions);
    mu_run_test(test__print_msg);
    // mu_run_test(test_failures);
    mu_run_test(test_dlclose);

    return NULL;
}

RUN_TESTS(all_tests);