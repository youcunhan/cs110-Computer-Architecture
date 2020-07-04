#include <stdio.h> /* for stderr */
#include <stdlib.h> /* for exit() */
#include <string.h>
#include "types.h"
#include "utils.h"
#include "riscv.h"
/* Contributor: youch */

void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_jalr(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_utype(Instruction, Processor *);
/* opcode */
#define RTYPE 0x33
#define ITYPE_LOAD 0x03
#define ITYPE_EXCEPT 0x13
#define ITYPE_JALR 0x67
#define ITYPE_ECALL 0x73
#define STYPE 0x23
#define SBTYPE 0x63
#define UTYPE_AUIPC 0x17
#define UTYPE_LUI 0x37
#define UJTYPE 0x6f

void execute_instruction(Instruction inst, Processor *p, Byte *memory) {
    switch(inst.opcode.opcode) {
        case RTYPE:
        {
            execute_rtype(inst, p);
            p->PC += 4;
            break;
        }
        case ITYPE_EXCEPT:
        {
            execute_itype_except_load(inst, p);
            p->PC += 4;
            break;
        }
        case ITYPE_LOAD:
        {
            execute_load(inst, p, memory);
            p->PC += 4;
            break;
        }
        case ITYPE_JALR:
        {
            execute_jalr(inst, p);
            break;
        }
        case ITYPE_ECALL:
        {
            execute_ecall(p, memory);
            break;
        }
        case STYPE:
        {
            execute_store(inst, p, memory);
            p->PC += 4;
            break;
        }
        case SBTYPE:
        {
            execute_branch(inst, p);
            break;
        }
        case UTYPE_AUIPC:
        {
            execute_utype(inst, p);
            p->PC += 4;
            break;
        }
        case UTYPE_LUI:
        {
            execute_utype(inst, p);
            p->PC += 4;
            break;
        }
        case UJTYPE:
        {
            execute_jal(inst, p);
            break;
        }
        default: /* undefined opcode */
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

void execute_rtype(Instruction inst, Processor *p) {
    int rd = (int)inst.rtype.rd;
    int rs1 = (int)inst.rtype.rs1;
    int rs2 = (int)inst.rtype.rs2;
    Register *R = p->R;
    switch(inst.rtype.funct3) {
        case 0x0:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*add*/
                    R[rd] = R[rs1] + R[rs2];
                    break;
                }
                case 0x01:
                {
                    /*mul*/
                    R[rd] = (bitSigner(R[rs1], 32) * bitSigner(R[rs2], 32)) & 0xffffffff;
                    break;
                }
                case 0x20:
                {
                    /*sub*/
                    R[rd] = R[rs1] - R[rs2];
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x1:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*sll*/
                    R[rd] = R[rs1] << R[rs2];
                    break;
                }
                case 0x01:
                {
                    /*mulh*/
                    R[rd] = ((sDouble)bitSigner(R[rs1], 32) * bitSigner(R[rs2], 32) >> 32) & 0xffffffff;
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x2:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*slt*/
                    R[rd] = (bitSigner(R[rs1], 32) < bitSigner(R[rs2], 32)) ? 1 : 0;
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x3:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*sltu*/
                    R[rd] = (R[rs1] < R[rs2]) ? 1 : 0;
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x4:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*xor*/
                    R[rd] = R[rs1] ^ R[rs2];
                    break;
                }
                case 0x01:
                {
                    /*div*/
                    R[rd] = bitSigner(R[rs1], 32) / bitSigner(R[rs2], 32);
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x5:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*srl*/
                    R[rd] = R[rs1] >> R[rs2];
                    break;
                }
                case 0x20:
                {
                    /*sra*/
                    /*take highest bit*/
                    int imm = R[rs2];
                    int bit = R[rs1] & 0x80000000;
                    R[rd] = R[rs1] >> imm;
                    if(bit != 0){
                        while(imm != 0){
                            R[rd] = R[rd] + (1 << (32 - imm));
                            imm--;
                        }
                    }
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x6:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*or*/
                    R[rd] = R[rs1] | R[rs2];
                    break;
                }
                case 0x01:
                {
                    /*rem*/
                    R[rd] = bitSigner(R[rs1], 32) % bitSigner(R[rs2], 32);
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        case 0x7:
        {
            switch(inst.rtype.funct7) {
                case 0x00:
                {
                    /*and*/
                    R[rd] = R[rs1] & R[rs2];
                    break;
                }
                default:
                    handle_invalid_instruction(inst);
                    exit(-1);
                    break;
            }
            break;
        }
        default:
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

void execute_itype_except_load(Instruction inst, Processor *p) {
    int funct7 = inst.itype.imm >> 5;
    int rd = (int)inst.itype.rd;
    int rs1 = (int)inst.itype.rs1;
    int imm = get_imm_operand(inst);
    Register *R = p->R;
    switch(inst.itype.funct3) {
        case 0x0:
        {
            /*addi*/
            R[rd] = R[rs1] + imm;
            break;
        }
        case 0x1:
        {
            if(funct7 == 0x00)
                /*slli*/
                R[rd] = R[rs1] << imm;
            else{
                handle_invalid_instruction(inst);
                exit(-1);
            }
                
            break;
        }
        case 0x2:
        {
            /*slti*/
            R[rd] = (bitSigner(R[rs1], 32) < imm) ? 1 : 0;
            break;
        }
        case 0x3:
        {
            /*sltiu*/
            R[rd] = (R[rs1] < ((unsigned)imm)) ? 1 : 0;
            break;
        }
        case 0x4:
        {
            /*xori*/
            R[rd] = R[rs1] ^ imm;
            break;
        }
        case 0x5:
        {
            int imm = inst.itype.imm & 0x1f;
            if(funct7 == 0x00)
                /*srli*/
                R[rd] = R[rs1] >> imm;
            else if(funct7 == 0x20){
                /*srai*/
                /*take highest bit*/
                int bit = R[rs1] & 0x80000000;
                R[rd] = R[rs1] >> imm;
                if(bit != 0){
                    while(imm != 0){
                        R[rd] = R[rd] + (1 << (32 - imm));
                        imm--;
                    }
                }
            }
            else{
                handle_invalid_instruction(inst);
                exit(-1);
            }
                
            break;
        }
        case 0x6:
        {
            /*ori*/
            R[rd] = R[rs1] | imm;
            break;
        }
        case 0x7:
        {
            /*andi*/
            R[rd] = R[rs1] & imm;
            break;
        }

        default:
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

void execute_ecall(Processor *p, Byte *memory UNUSED) {
    int a0 = bitSigner(p->R[10], 32);
    switch(a0) {
        case 1:
        {
            /*print integer in a1*/
            int a1 = bitSigner(p->R[11], 32);
            printf("%d", a1);
            p->PC += 4;
            break;
        }
        case 4:
        {
            /*print string in a1*/
            int a1 = p->R[11];
            char tmp = (char)load(memory, a1, 1, 0);
            while(tmp != '\0' && a1 < MEMORY_SPACE){
                printf("%c", tmp);
                a1++;
                tmp = (char)load(memory, a1, 1, 0);
            }
            p->PC += 4;
            break;
        }
        case 10:
        {
            /*exit*/
            printf("exiting the simulator\n");
            exit(0);
            break;
        }
        case 11:
        {
            /*print char in a1*/
            char a1 = p->R[11];
            printf("%c", a1);
            p->PC += 4;
            break;
        }
        default: /* undefined ecall */
            printf("Illegal ecall number %d\n", a0); /* What stores the ecall arg? */
            exit(-1);
            break;
    }
}

void execute_branch(Instruction inst, Processor *p) {
    int branchaddr = p->PC + get_branch_offset(inst);
    int rs1 = (int)inst.sbtype.rs1;
    int rs2 = (int)inst.sbtype.rs2;
    Register* R = p->R;
    /* Remember that the immediate portion of branches
       is counting half-words, so make sure to account for that. */
    
    switch(inst.sbtype.funct3) {
        case 0x0:
        {
            /*beq*/
            if(R[rs1] == R[rs2])
                p->PC = branchaddr;
            else
                p->PC += 4;
            break;
        }
        case 0x1:
        {
            /*bne*/
            if(R[rs1] != R[rs2])
                p->PC = branchaddr;
            else
                p->PC += 4;
            break;
        }
        case 0x4:
        {
            /*blt*/
            if(bitSigner(R[rs1], 32) < bitSigner(R[rs2], 32))
                p->PC = branchaddr;
            else
                p->PC += 4;
            break;
        }
        case 0x5:
        {
            /*bge*/
            if(bitSigner(R[rs1], 32) >= bitSigner(R[rs2], 32))
                p->PC = branchaddr;
            else
                p->PC += 4;
            break;
        }
        case 0x6:
        {
            /*bltu*/
            if(R[rs1] < R[rs2])
                p->PC = branchaddr;
            else
                p->PC += 4;
            break;
        }
        case 0x7:
        {
            /*bgeu*/
            if(R[rs1] >= R[rs2])
                p->PC = branchaddr;
            else
                p->PC += 4;
            break;
        }
        default:
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

void execute_load(Instruction inst, Processor *p, Byte *memory) {
    int rd = (int)inst.itype.rd;
    int rs1 = (int)inst.itype.rs1;
    int offset = get_imm_operand(inst);
    Register *R = p->R;
    switch(inst.itype.funct3) {
        case 0x0:
        {
            /*lb*/
            R[rd] = bitSigner(load(memory, R[rs1] + offset, 1, 0), 8);
            break;
        }
        case 0x1:
        {
            /*lh*/
            R[rd] = bitSigner(load(memory, R[rs1] + offset, 2, 0), 16);
            break;
        }
        case 0x2:
        {
            /*lw*/
            R[rd] = bitSigner(load(memory, R[rs1] + offset, 4, 0), 32);
            break;
        }
        case 0x4:
        {
            /*lbu*/
            R[rd] = load(memory, R[rs1] + offset, 1, 0);
            break;
        }
        case 0x5:
        {
            /*lhu*/
            R[rd] = load(memory, R[rs1] + offset, 2, 0);
            break;
        }
        default:
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

void execute_store(Instruction inst, Processor *p, Byte *memory) {
    int rs2 = (int)inst.stype.rs2;
    int offset = get_store_offset(inst);
    int rs1 = (int)inst.stype.rs1;
    Register *R = p->R;
    switch(inst.stype.funct3) {
        case 0x0:
        {
            /*sb*/
            store(memory, R[rs1] + offset, 1, R[rs2], 0);
            break;
        }
        case 0x1:
        {
            /*sh*/
            store(memory, R[rs1] + offset, 2, R[rs2], 0);
            break;
        }
        case 0x2:
        {
            /*sw*/
            store(memory, R[rs1] + offset, 4, R[rs2], 0);
            break;
        }
        default:
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

void execute_jal(Instruction inst, Processor *p) {
    Address nextPC = p->PC + get_jump_offset(inst);
    int rd = (int)inst.ujtype.rd;
    p->R[rd] = p->PC + 4;
    p->PC = nextPC;
}

void execute_jalr(Instruction inst, Processor *p) {
    int rd = (int)inst.itype.rd;
    int rs1 = (int)inst.itype.rs1;
    Address nextPC = p->R[rs1] + get_imm_operand(inst);
    p->R[rd] = p->PC + 4;
    p->PC = nextPC;
}

void execute_utype(Instruction inst, Processor *p) {
    int imm = bitSigner(inst.utype.imm,20) << 12;
    int rd = (int)inst.utype.rd;
    Register *R = p->R;
    switch(inst.utype.opcode) {
        case 0x17:
        {
            /*auipc*/
            R[rd] = (int)p->PC + imm;
            break;
        }
        case 0x37:
        {
            /*lui*/
            R[rd] = imm;
            break;
        }
        default:
            handle_invalid_instruction(inst);
            exit(-1);
            break;
    }
}

/* Checks that the address is aligned correctly */
int check(Address address, Alignment alignment) {
    if(address > 0 && address < MEMORY_SPACE) {
        if(alignment == LENGTH_BYTE) {
            return 1;
        }
        else if(alignment == LENGTH_HALF_WORD) {
            return address%2 == 0;
        }
        else if(alignment == LENGTH_WORD) {
            return address%4 == 0;
        }
    }
    
    return 0;
}

void store(Byte *memory, Address address, Alignment alignment, Word value, int check_align) {
    if((check_align && !check(address, alignment)) || (address >= MEMORY_SPACE)) {
        handle_invalid_write(address);
    }
    memcpy(memory+address,&value,alignment);

}

Word load(Byte *memory, Address address, Alignment alignment, int check_align) {
    Word data = 0; /* initialize our return value to zero */

    if((check_align && !check(address, alignment)) || (address >= MEMORY_SPACE)) {
        handle_invalid_read(address);
    }
    switch(alignment){
        case 4:
        {
            data = memory[address] + (memory[address + 1] << 8) + (memory[address + 2] << 16) + (memory[address + 3] << 24);
            break;
        }
        case 2:
        {
            data = memory[address] + (memory[address + 1] << 8);
            break;
        }
        case 1:
        {
            data = memory[address];
            break;
        }
    }

    return data;
}


