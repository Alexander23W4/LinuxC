#include "c16.h"
#include "debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int32_t I32_the_size__ex = 1000;
static int32_t I32_the_age__s = 30;

int32_t I32_get_age(){
    return I32_the_age__s;
}

void V_set_age(int32_t age){
    I32_the_age__s = age;
}

double D_update_ratio(double new_ratio){
    static double D_ratio__s = 1.0;
    double old_ratio = D_ratio__s;
    D_ratio__s = new_ratio;
    return old_ratio;
}

void V_print_size()
{
    log_info("I think size is: %d", I32_the_size__ex);
}