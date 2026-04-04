#include <stdio.h>
int f(){
    return 0x123;
}

int g(){
    return -123;
}

int h(){
    return 0b101010;
}

int x __attribute__((unused));
__attribute__((noinline)) int g(){ return 1 / 0; }

__attribute__((noinline)) long double g(int x0, long double x1, int x2){
   return x0 + x1 + x2;
}

__test_g(){
   g(0, 0.0, 1);
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