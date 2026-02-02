#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#define MEMORY_ALLOCATION_ERROR "MEMORY ALLOCATION ERROR"


void _die(const char* _msg){
    if(errno){
        perror(_msg);
    }
    else{
        printf("ERROR: %s\n", _msg)
    }
}

// function pointer:
typedef int32_t(*Fp_cal2)(int a, int b);

int32_t* I32_bubble_sort(int32_t* numbers, int count, Fp_cal2 cal){
    int32_t* temp = 0;
    int32_t* target = (int32_t*)malloc(sizeof(int32_t) * count);
    if(!target) _die(MEMORY_ALLOCATION_ERROR);

    memcpy(target, numbers, sizeof(int32_t) * count);
    for(size_t i = 0; i < count; i++){
        for(size_t j = 0; j < count - 1; j++){
            if(cal(target[j], target[j+1]) > 0){
                temp = target[j];
                target[j] = target[j+1];
                target[j+1] = temp;
            }
        }
    }
    return target;
}

int32_t I32_sorted_order(int32_t a, int32_t b) {return a - b;}

int32_t I32_reverse_order(int32_t a, int32_t b) {return b - a;}

void V_test_sorting__T(int32_t* numbers, int count, Fp_cal2 cal){
    int32_t* sorted = I32_bubble_sort(numbers, count, cal);
    if(!sorted) _die("FAILED TO SORT");
    
    // [print out]
    free(sorted);
}



