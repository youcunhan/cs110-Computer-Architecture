#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
/* Contributor: youch */

int bitSigner(unsigned int field, unsigned int size) {
    int result = 0, i, last_bit;
    for(i = 0;i < (int)size - 1;i++){
        /*take last bit*/
        last_bit = field & 0x1;
        result += last_bit << i;
        field >>= 1;
    }
    last_bit = field & 0x1;
    result -= last_bit << i;
    return result;
}

/* You may find implementing this function handy */
int get_imm_operand(Instruction inst) {
    return bitSigner(inst.itype.imm, 12);
}

/* Remember that the offsets should return the offset in BYTES */

int get_branch_offset(Instruction inst) {
    return bitSigner((inst.sbtype.imm5 >> 1 << 1) + ((inst.sbtype.imm7 & 0x3f) << 5) + ((inst.sbtype.imm5 & 1) << 11) + (inst.sbtype.imm7 >> 6 << 12), 13);
}

int get_jump_offset(Instruction inst) {
    int imm0_10 = (inst.ujtype.imm & 0x7fe00) >> 8;
    int imm11 = (inst.ujtype.imm & 0x00100) << 3;
    int imm12_19 = (inst.ujtype.imm & 0x000ff) << 12;
    int imm20 = (inst.ujtype.imm & 0x80000) << 1;
    int imm = imm0_10 + imm11 + imm12_19 + imm20;
    return bitSigner(imm, 21);
}

int get_store_offset(Instruction inst) {
    return bitSigner((inst.stype.imm7 << 5) + inst.stype.imm5, 12);
}

void handle_invalid_instruction(Instruction inst) {
    printf("Invalid Instruction: 0x%08x\n", inst.bits); 
}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}

