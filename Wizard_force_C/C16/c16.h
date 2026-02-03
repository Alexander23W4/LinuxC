#ifndef __C16_H__
#define __C16_H__
#include <stdint.h>
// Make THE_SIZE in c16.c available in other files
extern int32_t I32_the_size__ex;

int32_t I32_get_age();
void V_set_age(int32_t age);

double D_update_ratio(double new_ratio);

void V_print_size();

#endif
