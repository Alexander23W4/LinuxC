#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define GPR_MASK 0x1F

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

*/
int operate(void);

int pc = 0;
int GPR[32] = {0};
int M[1024] = {0};

int main(int argc, char** argv){
    // load the codes into memory

    // operate until the very end
    
}

int32_t sign_extend_s_type(uint32_t code) {
    int imm11_5 = (code >> 25) & 0x7F;    // bit[31:25]
    int imm4_0 = (code >> 7) & 0x1F;      // bit[11:7]  
    int imm11 = (code >> 31) & 1;         
    
    return (imm11 << 11) | (imm11_5 << 5) | (imm4_0);  
}


int32_t sign_extend(uint32_t instr, int bit_width) {

    uint32_t field = (instr >> (32 - bit_width)) & ((1 << bit_width) - 1);
    
    if (field & (1 << (bit_width - 1))) {
        return field | (~0U << bit_width);
    } else {

        return field;
    }
}

int operate(void){
    int code = M[pc >> 2];    // fetch
    // decode operate update
    int opcode = code & 0x7F;
    int opcode__a = (code & 0x7000) >> 12;
    int next = 0;
    switch(opcode){
        case 0b1100111:   // jalr   jump and link 
            int32_t imm = sign_extened(code >> 20, 12);
            int32_t rs = (code >> 15) & 0x1F;
            int32_t rd = (code >> 7) & 0x1F;
            if(rd != 0) GPR[rd] = pc + 4;
            next = (imm + GPR[rs]) & ~1;    // ~1 is reversed code of 1(0000....0001)
            break;

        case 0b0010011:   // addi    // add immediate
            int32_t imm = sign_extened(code >> 20, 12);
            int32_t rs = (code >> 15) & 0x1F;
            int32_t rd = (code >> 7) & 0x1F;
            GPR[rd] = GPR[rs] + imm;
            next = pc + 4;
            break;

        case 0b0110011:   // add    // add register-register
            int32_t rs1 = (code >> 20) & 0x1F;
            int32_t rs2 = (code >> 15) & 0x1F;
            int32_t rd = (code >> 7) & 0x1F;
            GPR[rd] = GPR[rs1] + GPR[rs2];
            next = pc + 4;
            break;

        case 0b0110111:   // lui (load upper immediate)
            int32_t imm = sign_extend((code >> 12) << 12, 32);
            int32_t rd = (code >> 7) & 0x1F;
            GPR[rd] = imm;
            next = pc +4;
            break;

        case 0b0000011:   // lw | lbu     // pull data from RAM to GPR
            assert(opcode__a == 0b010 || opcode__a == 0b100);
            int rs1 = (code >> 15) & 0x1F;
            int rd = (code >> 7) & 0x1F;
            int32_t imm = sign_extend(code >> 20, 12);
            if(opcode__a == 0b010){ // lw
                GPR[rd] = M[(GPR[rs1] + imm) >> 2];
            }
            else{    // lbu
                uint32_t addr = GPR[rs1] + imm;
                uint32_t word_idx = addr >> 2;
                int byte_offset = addr & 0x3;
                
                uint32_t word = M[word_idx];
                uint8_t byte_val;
                
                byte_val = (word >> (byte_offset * 8)) & 0xFF;
                GPR[rd] = byte_val; 
            }
            next = pc + 4;
            break;

        case 0b0100011:   // sw | sb
            assert(opcode__a == 0b010 || opcode__a == 0b000);
            int funct3 = (code >> 12) & 0x7;
            int rs1 = (code >> 15) & 0x1F;
            int rs2 = (code >> 20) & 0x1F;  
            int32_t imm = sign_extend_s_type(code);  
            
            uint32_t addr = GPR[rs1] + imm;
            uint32_t word_idx = addr >> 2;
            int byte_off = addr & 3;
            
            if (funct3 == 0b010) {  // SW
                M[word_idx] = GPR[rs2]; 
            } 
            else if (funct3 == 0b000) {  // SB
                uint32_t word = M[word_idx];
                word &= ~(0xFF << (byte_off * 8));  
                word |= ((GPR[rs2] & 0xFF) << (byte_off * 8));  
                M[word_idx] = word;
            }
            next = pc + 4;
            break;

        default:
            next = -1;
            break;
    }
    return next;
}




