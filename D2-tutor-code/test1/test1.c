#include <stdio.h>
#include <stdint.h>
int f(){
    return 0x123;
}

int32_t g(){
    return -123;  // this is 32-bits num, but less than 20 bits, addi or (lui (20)| addi(12))
}

int8_t h(){
    return 0b101010;  // only addi?
}

int32_t g2(){
   return 0x1234abc;  // addi a0 abc   lui a0 01234
}

int k(){
   uint64_t a = 0x6789abcd0101123f;  // put into register or memory
   printf("test: %d\n", a);
}

int x __attribute__((unused));
__attribute__((noinline)) int g(){ return 1 / 0; }

__attribute__((noinline)) long double g(int x0, long double x1, int x2){
   return x0 + x1 + x2;
}

__test_g(){
   g(0, 0.0, 1);
}
// static data area, stack, heap, text

// macro is directly copied to their utlized position, without pre-compilation
#define MAX_CNT 10   // distribution

#define __TEST_(n, ...) return a##n  // distribution

// distribution
#define __TEST1_(n, a, ...) {printf(\
"test: %d", a);}\

__test_c(){
   for (size_t i = 0; i < MAX_CNT; i++)
   {
      test_g();
      uint64_t a = 10;
      // ... 
   }
}

// riscv64-unknown-elf-gcc -march=rv32i   -mabi=ilp32   -O2 -c test1.c
// riscv64-unknown-elf-objdump -d -M no-aliases test1.o


/*
dive deep into how c program compiled, use what kind of instr or instr_combo
I already know that compiler should do:
Compilation (3 checking, intermediate language -> optimization) -> assembly(.s) -> .o(binary)
Linking

test.c (源代码)
   ↓ 预处理 (preprocessing)
test.i (预处理后的代码)
   ↓ 编译 (compilation)
test.s (汇编语言文件，文本格式)  ← **这才是汇编文件**
   ↓ 汇编 (assembly)
test.o (目标文件，二进制机器码)  ← **不是汇编文件**
   ↓ 链接 (linking)
test (可执行文件)

I could use objdump push .o file (not linked) back to assembly,
 check which specific instr compiler use for explain this c program

------------------------------------
Instr level arrangement:

-> How to load 32 bits constant
 

*/