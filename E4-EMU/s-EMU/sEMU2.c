#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "./debug_macro.h"
/*
RUNTIME ENVIRONMENT:
From another perspective, in order to make the program’s functionalities richer, 
we can not only add more instructions but also provide a more powerful runtime environment for the program. 
Below we attempt to add more functionalities to sEMU.
*/
/*
sISA

The opcode : add li bner0 
 7  6 5  4 3   2 1   0
+----+----+-----+-----+
| 00 | rd | rs1 | rs2 | R[rd]=R[rs1]+R[rs2]      ADD instruction for register addition
+----+----+-----+-----+
| 10 | rd |    imm    | R[rd]=imm               LI instruction (Load Immediate with zero-extension)
+----+----+-----+-----+
| 11 |   addr   | rs2 | if (R[0]!=R[rs2]) PC=addr BNER0 instruction (Branch if Not Equal to Register 0)
+----+----------+-----+

*/
uint8_t pc = 0;
uint8_t GPR[4];
uint8_t M[16];
/*
Fill Momery with 
0: li r0, 10   # This is decimal 10.
1: li r1, 0
2: li r2, 0
3: li r3, 1
4: add r1, r1, r3
5: add r2, r2, r1
6: out xx, xx, r2
7: bner0 4, r1
8: bner0 7, r3
*/

void _v_fill_memory(int add_target)   // add_target: 1 + 2 + ... + add_target
{
    log_info("Filling memory.");
    M[0] = 0b10000000 | (add_target & 0x0F);
    M[1] = 0b10010000;
    M[2] = 0b10100000;
    M[3] = 0b10110001;
    M[4] = 0b00010111;
    M[5] = 0b00101001;
    M[6] = 0b01000010;
    M[7] = 0b11010001;
    M[8] = 0b11011111;
}
uint8_t operate(void);
uint8_t next_pc;
int main(int argc, char** argv)
{
    assert(argc >= 2);
    int target = atoi(argv[1]);
    check((target != 0 && target < 16), "Invalid command line argv input");
    _v_fill_memory(target); // fill memory
    log_info("CPU running.");
    while(pc != 8){
        next_pc = operate();
        if(pc != 99){   // 99: error_pc_code, operation error or initailization error
            pc = next_pc;
        }
        else{
            log_err("PC reach invalid code, operation error.");
            printf("Error\n");
            break;
        }
    }
    return 0;
error:
    return -1;
}

uint8_t operate(void){
    uint8_t next = 0;
    uint8_t code = M[pc];    // Fetch is already downed
    // Decode, Execute, Update_PC: 
    switch(code >> 6){
        case 0b00:
            log_info("ADD");   
            GPR[(code & 0b00110000) >> 4] = GPR[(code & 0b00001100) >> 2] + GPR[(code & 0b00000011)];
            next = pc + 1;
            break;
        case 0b01:
            log_info("OUT");  
            printf("Result: %d\n", GPR[code & 0b00000011]);   // out rs2
            next = pc + 1;
            break;
        case 0b10:
            log_info("LI");  
            GPR[(code & 0b00110000) >> 4] = (code & 0b00001111);
            next = pc + 1;
            break;
        case 0b11:
            log_info("BNER0");  
            next = (GPR[(code & 0b00000011)] == GPR[0]) ? (pc + 1) : ((code & 0b00111100) >> 2);
            break;
        default:
            next = 99;
            break;     
    }
    return next;
}





