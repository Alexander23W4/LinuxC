#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "../dbg.h"


int print_a_message(const char *msg)
{
    printf("A STRING: %s\n", msg);

    return 0;
}


int uppercase(const char *msg)
{
    int i = 0;
    if (msg == NULL) return -1;

    for(i = 0; msg[i] != '\0'; i++) {
        printf("%c", toupper((unsigned char)msg[i]));
    }

    printf("\n");

    return 0;
}

int lowercase(const char *msg)
{
    int i = 0;
    if (msg == NULL) return -1;

    for(i = 0; msg[i] != '\0'; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;
}

// print first n char in string msg
// ** length < n 
int _print_msg(const char* msg, int n){
    assert(n >= 0);
    int length = (int)strlen(msg);
    int temp = length > n ? n : length;
    for (int i = 0; i < temp; i++)
    {
        printf("%c", msg[i]);
    }
    printf("\n");
    return 0;
}

// int fail_on_purpose(const char *msg)
// {
//     return 1;
// }