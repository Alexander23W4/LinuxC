#include <stdio.h>
#include <stdint.h>

// how compiler deal with num & variables

// if no main, whether it could be compiled ?

// noinline && default


__attribute__((noinline)) int f(){   
    // noinline, no parameters, 
    // random reg = text_addr(save return addr) -> jar(to target reg) 
    // -> Mf/regf = 0x123 () -> ret
    return 0x123;
}

int g(){  // default
    return -123;
}

int h(){  // default
    return 0b101010;
}

__attribute__((noinline)) uint64_t k(){
    uint64_t a = 0x6789abcd0101123f;  // put into register or memory
    return a;
}

__attribute__((noinline)) uint32_t k2(){
    uint64_t a = 0x6789abcd0101123f;  // put into register or memory
    return a;
}

int main(){
    int F = f();   // F = Mf/regf

    return 0;
}

// __attribute__((noinline)) uint64_t h64(uint64_t num){
//     return num + 0b101010;
// }

// __attribute__((noinline)) int k(){
//    uint64_t a = 0x6789abcd0101123f;  // put into register or memory
//    return h64(a);
// }

