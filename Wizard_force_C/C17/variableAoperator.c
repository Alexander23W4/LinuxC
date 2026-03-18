// bit operator: ~ | ^ &    >> << 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
//----------------------------------enum---------------------------------------
enum {
    OPEN = 10,
    DOWN,
    FALSE,
}; 

// equal to :

#define OPEN 10
#define DOWN 11
#define FLASE 12

// 
#ifndef FLASE
#define TRUE 100
#endif

// static use is more common
static enum {
    ONE,
    TWO,
    THREE
};

// enum with number
typedef enum {
    PHYSICAL,
    PHYSIOLOGICAL,
    BIOLOGICAL,
} academy;

static academy current_research_concentration;  
// enum variable could work as state container
// which is like State in verilog
/*
--verilog--
reg [1:0] State   // enum variable
localparam RUN = 1, STAY = 2, IDEL = 0  // enum (state)
*/

// switch(current_research_concentration){  
//     case PHYSICAL:
//     case PHYSIOLOGICAL:
//     case BIOLOGICAL:
//     default:
// }

//---------------------------------volatile register--------------------------------

// if variable is volatile, every time the variable is operated, the memory/register must be read/write, can not be optimized
volatile int operation = 0;   // volatile not statistic type

void test(){
    register int index;

    for (index = 0; index < 100; index++)
    {
        operation += index;
    }
}

/*
if operation is not volatile
int operation = 0;

for (...) {
    operation += index;
}

compiler may optimized the loop as:

operation = 4950
*/

// volatile usage   ***(In hardware simulation || embedded-C --> volatile is essential)
void test2(){
    // 1
    volatile uint32_t* reg = malloc(sizeof(uint32_t));
    *reg = (uint32_t *)0x10000000;
    *reg = 1;
    free(reg);

    // 2
    volatile int flag;   // interrupt cordinate variable
}


// -----------------------------------flexibel numbers-------------------------------------

// These type are more flexible 
// These MACRO are more transplant friendly  

// flexibel than int32_t fix length
int_least32_t random = 0;
int_fast32_t fast = 0;

void test3(){
    int_least16_t* arr = malloc(100 * sizeof(int_least16_t));
    int_least16_t* temp = arr + 2;
    
    size_t size = sizeof(int_least16_t);    // memory size
    ptrdiff_t diff = temp - arr; // pointer gap
    intptr_t ptr = (intptr_t)arr;  // pointer -> integer
    // if ----- arr = 0x7ffd12345678
    // then --- ptr = 140725947000000
}


fast = (INT32_MAX > 3200000000) ? INT_FAST32_MAX - 1 : INT_LEAST32_MAX - 1;


 