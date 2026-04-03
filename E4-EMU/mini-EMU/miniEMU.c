#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define _GPR_MASK 0x1F
#define OPERATING_CIRCLE_TERMINATION__MEM 6000
#define OPERATING_CIRCLE_TERMINATION__SUM 6000
#define GPR_AMOUNT 32
#define GENERAL_BIT_WIDTH 32
#define MEMORY_AMOUNT 524288  // 2MB
#define MEMORY_LOAD_EFFECTIVENESS 2000   // instr stored memory range

/*
mini-RV ISA   8 in total:

imm[11:0] rs1 000 rd 1100111 JALR
imm[11:0] rs1 000 rd 0010011 ADDI
0000000 rs2 rs1 000 rd 0110011 ADD
imm[31:12] rd 0110111 LUI
imm[11:0] rs1 010 rd 0000011 LW
imm[11:0] rs1 100 rd 0000011 LBU
imm[11:5] rs2 rs1 010 imm[4:0] 0100011 SW
imm[11:5] rs2 rs1 000 imm[4:0] 0100011 SB

000000000001 00000 000 00000 1110011 (0x00100073) EBREAK  
0x00000513   HALT
*/
int operate(int32_t* M);
void output_elements(int circle, int next, int32_t* M);
void load_memory(char* filename, int32_t* M);
int add_ebreak(int32_t* M);

uint32_t pc = 0;
int32_t GPR[GPR_AMOUNT] = {0};  // store signed number
// int32_t M[MEMORY_AMOUNT] = {0};

int _operating_circles = 0;
int next = 0;  // next pc

int main(int argc, char** argv){
    // load the codes into memory
    int32_t* M = (int32_t*)malloc(MEMORY_AMOUNT); 
    if (M == NULL) {
        perror("malloc failed");
        exit(1);
    }
    printf("DISTRIBUTED %zu BYTES (%.1f KB)\n", 
       MEMORY_AMOUNT * sizeof(int32_t), 
       MEMORY_AMOUNT * sizeof(int32_t) / 1024.0);

    assert(argc >= 2);
    load_memory(argv[1], M);
    int _SUCESSFUL_ADD_EBREAK = add_ebreak(M);
    assert(_SUCESSFUL_ADD_EBREAK);

    // operate until the very end
    while(next != -99){
        next = operate(M);
        assert(next != -1);  // if == -1, fail to decode 
        pc = next;
        output_elements(_operating_circles, next, M);         // print all variants (GPRs) for each loop
        _operating_circles++;
    }
    if(GPR[10] != 0){   // after operation check
        printf("HIT BAD TRAP\n");
        printf("ERROR, PROGRAM ENDED, X0 is not equal to 0\n");
    }
    else{
        printf("HIT GOOD TRAP\n");
    }
    free(M);
}

void load_memory(char* filename, int32_t* M){   
    FILE *fp = fopen(filename, "rb");  
    assert(fp);
// get instr amount
    // fseek(fp, 0, SEEK_END);
    // long total_bytes = ftell(fp);
    // fseek(fp, 0, SEEK_SET);    
    size_t loaded_instr = fread(M, sizeof(uint32_t), MEMORY_LOAD_EFFECTIVENESS, fp);
    fclose(fp);

    printf("--LOAD %zu AMOUNTS OF INSTR TO M[]\n", loaded_instr);
}

int add_ebreak(int32_t* M){
    for (size_t i = 0; i < MEMORY_LOAD_EFFECTIVENESS; i++)  
    {
        if(M[i] == 0x00000513){
            M[i + 1] = 0x00100073;
            return 1;
        }
    }  
    return 0;
}

void print_binary_int32(int32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0) printf(" ");  
    }
    printf("\n");
}


void output_elements(int circle, int next, int32_t* M){     // &&&
    printf("---%d---", circle);
    for(int i = 0; i < GPR_AMOUNT; i++){    // scan gpr
        printf("GPR %d: %d\n", i, GPR[i]);
    }
    printf("NEXT: %d\n", next);   // next pc
    if(next != -99){
        printf("NEXT INSTR: ");   // next instr
        print_binary_int32(M[next >> 2]);
    }
    printf("\n\n");
}

int32_t imm_conbination__s_type(uint32_t code) {   // combine two parts of imm
    int imm11_5 = (code >> 25) & 0x7F;    // bit[31:25]
    int imm4_0 = (code >> 7) & 0x1F;      // bit[11:7]      
    
    return (imm11_5 << 5) | (imm4_0);  
}


int32_t sign_extend(int num, int bit_width) {    // &&&  

    int32_t result;
    int signed_bit = (num >> (bit_width - 1)) & 1;  // get signed bit 
    if(signed_bit == 0){
        result = num | 0x00000000;   // number itself + extend 0
    }
    else{
        result = ((0xFFFFFFFF >> bit_width) << bit_width) | num;  // law bit_width bits remains 0, others->1
    }
    return result;
}

int operate(int32_t* M){
    uint32_t code = M[pc >> 2];

    int opcode = code & 0x7F;
    int funct3 = (code >> 12) & 0x7;

    int rs1 = (code >> 15) & 0x1F;
    int rs2 = (code >> 20) & 0x1F;
    int rd  = (code >> 7)  & 0x1F;

    int32_t imm;
    int next = 0;

    switch(opcode){

        case 0b1100111:   // JALR
            imm = sign_extend(code >> 20, 12);
            if(rd != 0) GPR[rd] = pc + 4;
            next = (GPR[rs1] + imm) & ~1;
            break;

        case 0b0010011:   // ADDI
            imm = sign_extend(code >> 20, 12);
            if(rd != 0) GPR[rd] = GPR[rs1] + imm;
            next = pc + 4;
            break;

        case 0b0110011:   // ADD
            if(rd != 0) GPR[rd] = GPR[rs1] + GPR[rs2];
            next = pc + 4;
            break;

        case 0b0110111:   // LUI
            if(rd != 0) GPR[rd] = code & 0xFFFFF000;
            next = pc + 4;
            break;

        case 0b0000011:   // LW / LBU
            imm = sign_extend(code >> 20, 12);
            if(funct3 == 0b010){   // LW
                uint32_t addr = GPR[rs1] + imm;
                uint32_t b0 = ((uint8_t*)M)[addr + 0];
                uint32_t b1 = ((uint8_t*)M)[addr + 1];
                uint32_t b2 = ((uint8_t*)M)[addr + 2];
                uint32_t b3 = ((uint8_t*)M)[addr + 3];
                if(rd != 0)
                    GPR[rd] = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
            }
            else if(funct3 == 0b100){   // LBU
                uint32_t addr = GPR[rs1] + imm;
                if(rd != 0)
                    GPR[rd] = ((uint8_t*)M)[addr];
            }
            else return -1;

            next = pc + 4;
            break;

        case 0b0100011: {   // SW / SB
            int imm_s = ((code >> 25) << 5) | ((code >> 7) & 0x1F);
            imm = sign_extend(imm_s, 12);

            uint32_t addr = GPR[rs1] + imm;

            if(funct3 == 0b010){   // SW
                uint32_t val = GPR[rs2];
                ((uint8_t*)M)[addr + 0] = val & 0xFF;
                ((uint8_t*)M)[addr + 1] = (val >> 8) & 0xFF;
                ((uint8_t*)M)[addr + 2] = (val >> 16) & 0xFF;
                ((uint8_t*)M)[addr + 3] = (val >> 24) & 0xFF;
            }
            else if(funct3 == 0b000){   // SB
                ((uint8_t*)M)[addr] = GPR[rs2] & 0xFF;
            }
            else return -1;

            next = pc + 4;
            break;
        }

        case 0b1110011:   // EBREAK
            return -99;

        default:
            return -1;
    }

    GPR[0] = 0;
    return next;
}



