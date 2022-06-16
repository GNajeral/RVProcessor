//
//  main.c
//  miprocesador
//
//  Created by Guillermo Nájera Lavid on 25/03/2022.
//

#include <stdio.h>
#include "instructions.h"
#include "compiler.h"

void loadAndStartProgram(){
    pc = 0;
    while((int8_t) memoryPool[pc] != -2){
        printf("PC: %X\n", pc);
        printf("Executing: %X(%X,%X,%X)\n", memoryPool[pc], memoryPool[pc+1],
               memoryPool[pc+2], memoryPool[pc+3]);
        switch (memoryPool[pc]) {
            case 0x1:
                add(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x2:
                addi(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x3:
                and(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x4:
                andi(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x5:
                auipc(memoryPool[pc], (memoryPool[pc+1]));
                break;
            case 0x6:
                beq(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x7:
                bge(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x8:
                bgeu(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x9:
                blt(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0xA:
                bltu(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0xB:
                bne(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0xC:
                jal(memoryPool[pc+1], memoryPool[pc+2]);
                break;
            case 0xD:
                jalr(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0xE:
                lb(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0xF:
                lbu(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x10:
                lh(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x11:
                lhu(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x12:
                lui(memoryPool[pc+1], memoryPool[pc+2]);
                break;
            case 0x13:
                lw(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x14:
                or(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x15:
                ori(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x16:
                sb(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x17:
                sh(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x18:
                sw(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x19:
                sll(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x1A:
                slli(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x1B:
                slt(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x1C:
                slti(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x1D:
                sltiu(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x1E:
                sltu(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x1F:
                sra(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x20:
                srai(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x21:
                srl(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x22:
                srli(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x23:
                sub(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x24:
                xor(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
            case 0x25:
                xori(memoryPool[pc+1], memoryPool[pc+2], memoryPool[pc+3]);
                break;
        }
    }
}

int main(int argc, const char * argv[]) {
    uint8_t passed = 0;
    uint8_t failed = 0;
    startMemory();
    startRegisters();
    printf("Starting with tests:\n");
    //Test 1 add instruction
    printf("--------------ADD INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 2, rs1: 1, rs2: 4\nADD(rd, rs1, rs2):\n");
    registers[1].value = 0x00000A12;
    registers[4].value = 0x000002BF;
    //add the values of rs1 and rs4 and store it in rs2;
    add(2, 1, 4);
    printf("Expected value: %X \nActual value: %X\n\n", 0x00000CD1, registers[2].value);
    if (registers[2].value == 0x00000CD1) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    //Restart memory and registers values
    startMemory();
    startRegisters();
    //Test 1 addi instruction
    printf("--------------ADDI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 4, immediate value: 0x000000FF\nADDI(rd, rs1, immediate value):\n");
    registers[4].value = 0x000A2EBA;
    int32_t immediate = 0x000000FF;
    addi(1, 4, immediate);
    printf("Expected value: %X \nActual value: %X\n\n", 0x000A2FB9, registers[1].value);
    if (registers[1].value == 0x000A2FB9) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 and instruction
    printf("--------------AND INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 4, rs2: 6\nAND(rd, rs1, rs2):\n");
    registers[3].value = 0x1426A4BF;
    registers[2].value = 0xFFFF0000;
    and(1, 3, 2);
    printf("Expected value: %X \nActual value: %X\n\n", 0x14260000, registers[1].value);
    if (registers[1].value == 0x14260000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 andi instruction
    printf("--------------ANDI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 4, immediate value: 0xFFFF0000\nANDI(rd, rs1, immediate value):\n");
    registers[3].value = 0x1426A4BF;
    registers[2].value = 0xFFFF0000;
    and(1, 3, 2);
    printf("Expected value: %X \nActual value: %X\n\n", 0x14260000, registers[1].value);
    if (registers[1].value == 0x14260000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 auipc instruction
    printf("--------------AUIPC INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, immediate value: 0x11111\nAUIPC(rd, immediate value):\n");
    printf("PC: 0x80204000\n");
    pc = 0x80204297;
    int32_t imm_u = 0x11111;
    auipc(1, imm_u);
    printf("Expected value: %X \nActual value: %X\n\n", 0x91315297, registers[1].value);
    if (registers[1].value == 0x91315297) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 beq instruction
    printf("--------------BEQ INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0x00000022, rs2 value: 0x00000022, immediate value: 0x00000024\nPC: 0x80204297\nBEQ(rs1, rs2, immediate value):\n");
    printf("PC: 0x80204000\n");
    pc = 0x80204000;
    int imm_b = 0x24;
    registers[1].value = 0x00000022;
    registers[2].value = 0x00000022;
    beq(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 2 bge instruction
    printf("TEST 2:\n\nrs1: 1, rs2: 2\nrs1 value: 0xF0000012, rs2 value: 0xF0000022, immediate value: 0x00000024\nPC: 0x80204000\nBEQ(rs1, rs2, immediate value):\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0xF0000012;
    registers[2].value = 0xF0000022;
    beq(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204004, pc);
    if (pc == 0x80204004) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 bgeu instruction
    printf("--------------BGEU INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0xFFFFFFFF, rs2 value: 0x00000022, immediate value: 0x00000024\nPC: 0x80204297\nBGEU(rs1, rs2, immediate value):\n");
    printf("PC: 0x80204000\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0xFFFFFFFF;
    registers[2].value = 0x00000022;
    bgeu(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 2 bgeu instruction
    printf("TEST 2:\n\nrs1: 1, rs2: 2\nrs1 value: 0x00000022, rs2 value: 0xFFFFFFFF, immediate value: 0x00000024\nPC: 0x80204000\nBGEU(rs1, rs2, immediate value):\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0x00000022;
    registers[2].value = 0xFFFFFFFF;
    bgeu(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204004, pc);
    if (pc == 0x80204004) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 blt instruction
    printf("--------------BLT INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0xF0000012, rs2 value: 0xF0000022, immediate value: 0x00000024\nPC: 0x80204297\nBLT(rs1, rs2, immediate value):\n");
    printf("PC: 0x80204000\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0xF0000012;
    registers[2].value = 0xF0000022;
    blt(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 2 blt instruction
    printf("TEST 2:\n\nrs1: 1, rs2: 2\nrs1 value: 0xF0000022, rs2 value: 0xF0000012, immediate value: 0x00000024\nPC: 0x80204000\nBLT(rs1, rs2, immediate value):\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0xF0000022;
    registers[2].value = 0xF0000012;
    blt(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204004, pc);
    if (pc == 0x80204004) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 bltu instruction
    printf("--------------BLTU INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0x00000022, rs2 value: 0xFFFFFFFF, immediate value: 0x00000024\nPC: 0x80204297\nBLTU(rs1, rs2, immediate value):\n");
    printf("PC: 0x80204000\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0x00000022;
    registers[2].value = 0xFFFFFFFF;
    bltu(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 2 bltu instruction
    printf("TEST 2:\n\nrs1: 1, rs2: 2\nrs1 value: 0xFFFFFFFF, rs2 value: 0x00000022, immediate value: 0x00000024\nPC: 0x80204000\nBLTU(rs1, rs2, immediate value):\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0xFFFFFFFF;
    registers[2].value = 0x00000022;
    bltu(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204004, pc);
    if (pc == 0x80204004) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 bne instruction
    printf("--------------BNE INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0x00000023, rs2 value: 0x00000022, immediate value: 0x00000024\nPC: 0x80204297\nBNE(rs1, rs2, immediate value):\n");
    printf("PC: 0x80204000\n");
    pc = 0x80204000;
    imm_b = 0x24;
    registers[1].value = 0x00000023;
    registers[2].value = 0x00000022;
    bne(1, 2, imm_b);
    printf("Expected value: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 jal instruction
    printf("--------------JAL INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1\nimmediate value: 0x00000024\nPC: 0x80204297\nJAL(rd, immediate value):\n");
    pc = 0x80204000;
    int imm_j = 0x24;
    jal(1, imm_j);
    printf("Expected value in rs1: %X \nActual value: %X\n", 0x80204004, registers[1].value);
    printf("Expected value in pc: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024 && registers[1].value == 0x80204004) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 jalr instruction
    printf("--------------JALR INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x00000024, immediate value: 0x00000024\nPC: 0x80204297\nJALR(rd, rs1, immediate value):\n");
    pc = 0x80204000;
    imm_j = 0x24;
    registers[2].value = 0x80204000;
    jalr(1, 2, imm_j);
    printf("Expected value in rs1: %X \nActual value: %X\n", 0x80204004, registers[1].value);
    printf("Expected value in pc: %X \nActual value: %X\n\n", 0x80204024, pc);
    if (pc == 0x80204024 && registers[1].value == 0x80204004) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lb instruction
    printf("--------------LB INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x000100, immediate value: 0x00000024\nLB(rd, rs1, immediate value):\n");
    memoryPool[0x00000124] = 0xAB;
    imm_j = 0x24;
    registers[2].value = 0x00000100;
    lb(1, 2, imm_j);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFFFFFAB, registers[1].value);
    if (registers[1].value == 0xFFFFFFAB) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lbu instruction
    printf("--------------LBU INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x000100, immediate value: 0x00000024\nLBU(rd, rs1, immediate value):\n");
    memoryPool[0x00000124] = 0xAB;
    imm_j = 0x24;
    registers[2].value = 0x00000100;
    lbu(1, 2, imm_j);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xAB, registers[1].value);
    if (registers[1].value == 0xAB) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lh instruction
    printf("--------------LH INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x000100, immediate value: 0x00000024\nLH(rd, rs1, immediate value):\n");
    memoryPool[0x00000124] = 0xAB;
    memoryPool[0x00000125] = 0xCD;

    imm_j = 0x24;
    registers[2].value = 0x00000100;
    lh(1, 2, imm_j);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFFFCDAB, registers[1].value);
    if (registers[1].value == 0xFFFFCDAB) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lh instruction
    printf("--------------LHU INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x000100, immediate value: 0x00000024\nLHU(rd, rs1, immediate value):\n");
    memoryPool[0x00000124] = 0xAB;
    memoryPool[0x00000125] = 0xCD;

    imm_j = 0x24;
    registers[2].value = 0x00000100;
    lhu(1, 2, imm_j);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xCDAB, registers[1].value);
    if (registers[1].value == 0xCDAB) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lui instruction
    printf("--------------LUI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1\nimmediate value: 0x00000024\nLUI(rd, rs1, immediate value):\n");
    imm_j = 0xABCDE;
    lui(1, imm_j);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xABCDE000, registers[1].value);
    if (registers[1].value == 0xABCDE000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lh instruction
    printf("--------------LW INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x000100, immediate value: 0x00000024\nLW(rd, rs1, immediate value):\n");
    memoryPool[0x00000124] = 0xAB;
    memoryPool[0x00000125] = 0xCD;
    memoryPool[0x00000126] = 0xEF;
    memoryPool[0x00000127] = 0x01;

    imm_j = 0x24;
    registers[2].value = 0x00000100;
    lw(1, 2, imm_j);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x01EFCDAB, registers[1].value);
    if (registers[1].value == 0x01EFCDAB) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 or instruction
    printf("--------------OR INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0xFFF00000, rs2: 0x00000FFF\nOR(rd, rs1,  rs2):\n");
    registers[2].value = 0xFFF00000;
    registers[3].value = 0x00000FFF;
    or(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFF00FFF, registers[1].value);
    if (registers[1].value == 0xFFF00FFF) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 lh instruction
    printf("--------------ORI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0xFFF00000, immediate value: 0x00000FFF\nORI(rd, rs1, immediate value):\n");
    registers[2].value = 0xFFF00000;
    int imm_i = 0x00000FFF;
    ori(1, 2, imm_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFF00FFF, registers[1].value);
    if (registers[1].value == 0xFFF00FFF) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 sb instruction
    printf("--------------SB INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0x000100, rs2 value:0x000012FF ,immediate value: 0x00000024\nSB(rs2, rs1, immediate value):\n");
    int imm_s = 0x24;
    registers[1].value = 0x00000100;
    registers[2].value = 0x000012FF;
    sb(2, 1, imm_s);
    printf("Expected value in address 0x00000124: %X \nActual value: %X\n", 0xFF, memoryPool[0x00000124]);
    if (memoryPool[0x00000124] == 0xFF) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 sh instruction
    printf("--------------SH INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0x000100, rs2 value:0x000012FF ,immediate value: 0x00000024\nSH(rs2, rs1, immediate value):\n");
    imm_s = 0x24;
    registers[1].value = 0x00000100;
    registers[2].value = 0x000012FF;
    sh(2, 1, imm_s);
    printf("Expected value in address 0x00000124 --> 0x00000125: %X \nActual value: %X\n", 0xFF12, (memoryPool[0x00000125] + (memoryPool[0x00000124]<<8)));
    if ((memoryPool[0x00000125] + (memoryPool[0x00000124]<<8)) == 0xFF12) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 sh instruction
    printf("--------------SW INSTRUCTION-----------------------------------\nTEST 1:\n\nrs1: 1, rs2: 2\nrs1 value: 0x000100, rs2 value:0xABCDEF12 ,immediate value: 0x00000024\nSW(rs2, rs1, immediate value):\n");
    imm_s = 0x24;
    registers[1].value = 0x00000100;
    registers[2].value = 0xABCDEF12;
    sw(2, 1, imm_s);
    printf("Expected value in address 0x00000124 --> 0x00000127: %X \nActual value: %X\n", 0x12EFCDAB, (memoryPool[0x00000127] + (memoryPool[0x00000126]<<8) + (memoryPool[0x00000125]<<16) + (memoryPool[0x00000124]<<24)));
    if ((memoryPool[0x00000127] + (memoryPool[0x00000126]<<8) + (memoryPool[0x00000125]<<16) + (memoryPool[0x00000124]<<24)) == 0x12EFCDAB) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Test 1 sll instruction
    printf("--------------SLL INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0x00000ABC, rs2 value:0x00000010\nSLL(rd, rs1, rs2):\n");
    registers[2].value = 0x00000ABC;
    registers[3].value = 0x00000010;
    sll(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x0ABC0000, registers[1].value);
    if (registers[1].value == 0x0ABC0000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 slli instruction
    printf("--------------SLLI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x00000ABC, immediate value:0x00000010\nSLLI(rd, rs1, immediate value):\n");
    int shamt_i = 0x00000010;
    registers[2].value = 0x00000ABC;
    slli(1, 2, shamt_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x0ABC0000, registers[1].value);
    if (registers[1].value == 0x0ABC0000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 slt instruction
    printf("--------------SLT INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0x00000006, rs2 value:0x00000008\nSLT(rd, rs1, rs2):\n");
    registers[2].value = 0x00000006;
    registers[3].value = 0x00000008;
    slt(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x00000001, registers[1].value);
    if (registers[1].value == 0x00000001) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 slti instruction
    printf("--------------SLTI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x00000006, immediate value:0x00000008\nSLTI(rd, rs1, immediate value):\n");
    imm_i = 0x00000006;
    registers[2].value = 0x00000008;
    slti(1, 2, shamt_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x00000001, registers[1].value);
    if (registers[1].value == 0x00000001) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Test 1 sltui instruction
    printf("--------------SLTUI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0xFFFFFFFF, immediate value:0x00000022\nSLTUI(rd, rs1, immediate value):\n");
    imm_i = 0x00000022;
    registers[2].value = 0xFFFFFFFF;
    slti(1, 2, shamt_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x00000001, registers[1].value);
    if (registers[1].value == 0x00000001) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 sltu instruction
    printf("--------------SLTU INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0x00000006, rs2 value:0x00000008\nSLTU(rd, rs1, rs2):\n");
    registers[2].value = 0x00000022;
    registers[3].value = 0xFFFFFFFF;
    sltu(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x00000001, registers[1].value);
    if (registers[1].value == 0x00000001) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 srl instruction
    printf("--------------SRL INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0x00000ABC, rs2 value:0x00000010\nSRL(rd, rs1, rs2):\n");
    registers[2].value = 0xABC00000;
    registers[3].value = 0x00000010;
    sra(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFFFABC0, registers[1].value);
    if (registers[1].value == 0xFFFFABC0) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 srli instruction
    printf("--------------SRLI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x00000ABC, immediate value:0x00000010\nSRLI(rd, rs1, immediate value):\n");
    shamt_i = 0x00000010;
    registers[2].value = 0xABC00000;
    srai(1, 2, shamt_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFFFABC0, registers[1].value);
    if (registers[1].value == 0xFFFFABC0) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 sra instruction
    printf("--------------SRA INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0x00000ABC, rs2 value:0x00000010\nSRA(rd, rs1, rs2):\n");
    registers[2].value = 0xABC00000;
    registers[3].value = 0x00000010;
    sra(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFFFABC0, registers[1].value);
    if (registers[1].value == 0xFFFFABC0) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 srai instruction
    printf("--------------SRAI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0x00000ABC, immediate value:0x00000010\nSRAI(rd, rs1, immediate value):\n");
    shamt_i = 0x00000010;
    registers[2].value = 0xABC00000;
    srai(1, 2, shamt_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0xFFFFABC0, registers[1].value);
    if (registers[1].value == 0xFFFFABC0) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 xor instruction
    printf("--------------XOR INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2, rs2: 3\nrs1 value: 0xFFF00FFF, rs2 value:0xFFFFFFFF\nXOR(rd, rs1, rs2):\n");
    registers[2].value = 0xFFF00FFF;
    registers[3].value = 0xFFFFFFFF;
    xor(1, 2, 3);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x000FF000, registers[1].value);
    if (registers[1].value == 0x000FF000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    //Test 1 srai instruction
    printf("--------------XORI INSTRUCTION-----------------------------------\nTEST 1:\n\nrd: 1, rs1: 2\nrs1 value: 0xFFFFFFFF, immediate value:0xFFF00FFF\nXORI(rd, rs1, immediate value):\n");
    imm_i = 0xFFF00FFF;
    registers[2].value = 0xFFFFFFFF;
    xori(1, 2, imm_i);
    printf("Expected value in rd: %X \nActual value: %X\n", 0x000FF000, registers[1].value);
    if (registers[1].value == 0x000FF000) {
        printf("PASSED\n");
        passed++;
    }
    else{
        printf("FAILED\n");
        failed++;
    }
    
    //Restart memory and registers values
    startMemory();
    startRegisters();
    
    printf("Number of tests passed: %d\nNumber of tests failed: %d\n\n", passed, failed);
    
    printf("--------------COMPILER TESTING-----------------------------------\n");
    //Change path value with your own
    FILE *file = fopen("Path of program.txt", "r");
    compile(file);
    printf("Compiling...\n");
    printf("Compiled!\n");
    printf("Starting execution...\n");
    loadAndStartProgram();
    printf("Program Ended\n");
    return 0;
}
