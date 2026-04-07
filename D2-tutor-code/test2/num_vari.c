#include <stdio.h>
#include <stdint.h>
// riscv64-linux-gnu-gcc -march=rv32i   -mabi=ilp32   -O1 -c num_vari.c
// riscv64-linux-gnu-objdump -d -M no-aliases num_vari.o      (objdump reassembly)

// rv32gcc -O0 -c num_vari.c
// rv32obj num_vari.o

// how compiler deal with num & variables

// if no main, whether it could be compiled ?   

// noinline && default

// -----------------------------------------------------------------------------
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
/*
    the compiler flag is by default use -O1 optimization option
*/
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// -----------------------------------------------------------------------------
__attribute__((noinline)) int f(){   
    // noinline, no parameters, 
    // random reg = text_addr(save return addr) -> jar(to target reg) 
    // -> Mf/regf = 0x123 () -> ret

    // when -O0, 
    // ------ addi sp sp -16, downward growing stack 
    // sw s0 12 sp   write sp -> M[s0 + 12] , store stack 
    // operations: variables store in a[x] t[x] stack_mem
    // lw s0,12(sp)  load content in stack
    // ------ addi sp sp 16
    return 0x123;
}

int32_t g(){
    return -123;  // this is 32-bits num, but less than 20 bits, addi or (lui (20)| addi(12))   // only addi, addi zero -123
}

int8_t h(){
    return 0b101010;  // only addi?  // yes, addi  and jalr zero 0 ra (rd = r0, means do not care present addr, imm = 0, next = ra(return addr))
}

int32_t g2(){
   return 0x1234abc;  // addi a0 abc   lui a0 01234   // lui a0 1235  addi a0 a0 -1348 (make big step, adjust little step)
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
    int F = f();   //  Mf/regf, lw xxx a0
    int32_t G = g();
    int32_t G2 = g2();
    return 0;
}

// __attribute__((noinline)) uint64_t h64(uint64_t num){
//     return num + 0b101010;
// }

// __attribute__((noinline)) int k(){
//    uint64_t a = 0x6789abcd0101123f;  // put into register or memory
//    return h64(a);
// }

