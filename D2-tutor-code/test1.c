int f(){
    return 0x123;
}

int g(){
    return -123;
}

int h(){
    return 0b101010;
}

// riscv64-unknown-elf-gcc -march=rv32i   -mabi=ilp32   -O2 -c test1.c
// riscv64-unknown-elf-objdump -d -M no-aliases test1.o