//
//  instructions.h
//  miprocesador
//
//  Created by Guillermo Nájera Lavid on 29/03/2022.
//

#ifndef instructions_h
#define instructions_h
#include <stdlib.h>
#include <stdbool.h>

//In 32 bits signed integers, the max value is 0x7FFFFFFF
//and the minimum negative number is 0x80000000
//These are the max and min values the registers will be able to store

typedef struct Register {
    uint8_t number;
    int32_t value;
} Register;

uint8_t memoryPool[1000];     //Memoria de 4KB --> 4 bytes * 1000
Register registers[32];
int32_t pc = 0x00000000;    //Inicialización de programa contador




void startMemory(){
    uint8_t memoryStarter = 0x00;
    for(int i = 0; i < sizeof(memoryPool)/sizeof(uint8_t); i++){
        memoryPool[i] = memoryStarter;
    }
}

void startRegisters(){
    for (int i = 0; i < sizeof(registers)/sizeof(Register); i++) {
        Register initialRegister;
        initialRegister.number = i;
        initialRegister.value = 0x00000000;
        registers[i] = initialRegister;
    }
}

//add instruction
void add(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value + registers[rs2].value;
        pc += 4;
    }
}

//add immediate value instruction
void addi(uint8_t rd, uint8_t rs1, int imm_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value + imm_i;
        pc += 4;
    }
}
//and instruction
void and(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value & registers[rs2].value;
        pc += 4;
    }
    
}
//and immediate value insruction
void andi(uint8_t rd, uint8_t rs1, int imm_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value & imm_i;
        pc += 4;
    }
    
}

//auipc instruction
void auipc(uint8_t rd, int32_t imm_u){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        imm_u = imm_u <<12;
        registers[rd].value = pc+imm_u;
        pc += 4;
    }
}

//Salto condicionado a que los valores de rs1 y rs2 sean iguales, en caso contrario se avanza el programa contador
void beq(uint8_t rs1, uint8_t rs2, int imm_b){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if (registers[rs1].value == registers[rs2].value) {
        if (imm_b % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed");
        }
        else{
            pc += imm_b;
        }
    }
    else{
        pc += 4;
    }
}

//Salto condicionado a que el valor contenido en el registro rs1
//sea mayor o igual al contenido en rs2
void bge(uint8_t rs1, uint8_t rs2, int imm_b){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if (registers[rs1].value >= registers[rs2].value) {
        if (imm_b % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed");
        }
        else{
            pc += imm_b;
        }
    }
    else{
        pc += 4;
    }
}

//Salto condicionado a que el valor contenido sin signo en el registro rs1 sea
//mayor o igual al contenido en rs2
void bgeu(uint8_t rs1, uint8_t rs2, int imm_b){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if ((uint32_t) registers[rs1].value >= (uint32_t) registers[rs2].value) {
        if (imm_b % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            pc += imm_b;
        }
    }
    else{
        pc += 4;
    }
}

//Salto condicionado a que el valor contenido en el registro rs1
//sea menor al contenido en rs2
void blt(uint8_t rs1, uint8_t rs2, int imm_b){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if (registers[rs1].value < registers[rs2].value) {
        if (imm_b % 2 != 0) {
            perror("Error:  odd memory addresses cannot be accessed ");
        }
        else{
            pc += imm_b;
        }
    }
    else{
        pc += 4;
    }
}

//Salto condicionado a que el valor sin signo contenido en el registro rs1 sea
//menor al contenido en rs2
void bltu(uint8_t rs1, uint8_t rs2, uint8_t imm_b){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if ((uint32_t) registers[rs1].value < (uint32_t) registers[rs2].value) {
        if (imm_b % 2 != 0) {
            perror("Error:  odd memory addresses cannot be accessed ");
        }
        else{
            pc += imm_b;
        }
    }
    else{
        pc += 4;
    }
}

//Salto condicionado a que el valor contenido en el registro rs1 sea
//distinto al contenido en rs2
void bne(uint8_t rs1, uint8_t rs2, int imm_b){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    
    else if (registers[rs1].value != registers[rs2].value) {
        if (imm_b % 2 != 0) {
            perror("Error:  odd memory addresses cannot be accessed ");
        }
        else{
            pc += imm_b;
        }
    }
    else{
        pc += 4;
    }
}

//Salto incondicional
void jal(uint8_t rd, int imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        if (imm_j % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            registers[rd].value = pc + 4;
            pc += imm_j;
        }
    }
}

//Salto incondicional de registro con exceso
void jalr(uint8_t rd, uint8_t rs1, int imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        if ((registers[rs1].value + imm_j) % 4 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            registers[rd].value = pc + 4;
            pc = registers[rs1].value + imm_j;
        }
    }
}

//Instrucción lb: cargar byte de la dirección de memoria contenida
//en el registro en un registro de destino
void lb(uint8_t rd, uint8_t rs1, int32_t imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_j;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            registers[rd].value = 0xffffff00 + memoryPool[offset];
            pc += 4;
        }
    }
}

//Instrucción lbu: cargar byte sin signo de la dirección de memoria
//contenida en el registro en un registro de destino
void lbu(uint8_t rd, uint8_t rs1, int32_t imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_j;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            registers[rd].value = 0x00000000 + memoryPool[offset];
            pc += 4;
        }
    }
}

//Instrucción lh: cargar media palabra (16 bits) de la dirección de memoria
//contenida en el registro rs1 en un registro de destino rd
void lh(uint8_t rd, uint8_t rs1, int32_t imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_j;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            //Little endian implementation
            uint16_t lowest = memoryPool[offset+1]<<8;
            uint8_t highest = memoryPool[offset];
            registers[rd].value = 0xffff0000 + lowest + highest;
            pc += 4;
        }
    }
}

//Instrucción lhu: cargar media palabra (16 bits) sin signo
//de la dirección de memoria contenida en el registro rs1 en
//un registro de destino rd
void lhu(uint8_t rd, uint8_t rs1, int32_t imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_j;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            //Little endian implementation
            uint16_t lowest = memoryPool[offset+1]<<8;
            uint8_t highest = memoryPool[offset];
            registers[rd].value = 0x00000000 + lowest + highest;
            pc += 4;
        }
    }
}

//Instrucción lui: carga en el registro rd el valor immediato imm_u
void lui(uint8_t rd, int32_t imm_u){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        imm_u = imm_u<<12;
        registers[rd].value = imm_u;
        pc += 4;
    }
}

//Instrucción lw: cargar una palabra entera de la dirección de memoria
//contenida en el registro rs1 en un registro de destino rd
void lw(uint8_t rd, uint8_t rs1, int32_t imm_j){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_j;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            //Little endian implementation
            uint32_t lowest = memoryPool[offset+3]<<24;
            uint32_t nextLowest = memoryPool[offset+2]<<16;
            uint16_t priorHighest = memoryPool[offset+1]<<8;
            uint8_t highest = memoryPool[offset];
            registers[rd].value = 0x00000000 + lowest + nextLowest + priorHighest + highest;
            pc += 4;
        }
    }
}

//Instrucción OR: se realiza la operación lógica OR entre los valores de rs1 y rs2,
//luego se almacena el resultado en rd
void or(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value | registers[rs2].value;
        pc += 4;
    }
}

//Instrucción ORI: se realiza la operación lógica OR entre el valor de rs1
//y un valor inmediato, luego se almacena el resultado en rd
void ori(uint8_t rd, uint8_t rs1, int32_t imm_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value | imm_i;
        pc += 4;
    }
}

//Instrucción SB: almacena el byte menos significativo del registro rs2
//en la posición de memoria indicada por el registro rs1 + el valor inmediato
void sb(uint8_t rs2, uint8_t rs1, int32_t imm_s){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rs2 == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_s;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            memoryPool[offset] = registers[rs2].value & 0x000000ff;
            pc += 4;
        }
    }
}

//Instrucción SH: almacena los dos bytes menos significativos del
//registro rs2 en la posición de memoria indicada por el registro
//rs1 + el valor inmediato
void sh(uint8_t rs2, uint8_t rs1, int32_t imm_s){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rs2 == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_s;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            memoryPool[offset] = registers[rs2].value & 0x000000ff;
            memoryPool[offset+1] = (registers[rs2].value & 0x0000ff00)>>8;
            pc += 4;
        }
    }
}

//Instrucción SW: almacena los 4 bytes (una palabra) del registro rs2 en la posición
//de memoria indicada por el registro rs1 + el valor inmediato
void sw(uint8_t rs2, uint8_t rs1, int32_t imm_s){
    if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rs2 == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t offset = registers[rs1].value + imm_s;
        if ((offset) % 2 != 0) {
            perror("Error: odd memory addresses cannot be accessed ");
        }
        else{
            memoryPool[offset] = registers[rs2].value & 0x000000ff;
            memoryPool[offset+1] = (registers[rs2].value & 0x0000ff00)>>8;
            memoryPool[offset+2] = (registers[rs2].value & 0x00ff0000)>>16;
            memoryPool[offset+3] = (registers[rs2].value & 0xff000000)>>24;
            pc += 4;
        }
    }
}

//Instrucción SLL: corre a la izquierda (rs2%32) todos los bytes de
//rs1, y almacena el resultado en rd
void sll(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t shiftValue = registers[rs2].value%32;
        registers[rd].value = registers[rs1].value<<shiftValue;
        pc += 4;
    }
}

//Instrucción SLLI: corre a la izquierda (valor_inmediato%32)
//todos los bytes de rs1, y almacena el resultado en rd
void slli(uint8_t rd, uint8_t rs1, int32_t shamt_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t shiftValue = shamt_i%32;
        registers[rd].value = registers[rs1].value<<shiftValue;
        pc += 4;
    }
}

//Instrucción SLT: si rs1 < rs2, entonces se pone el valor 1 en rd.
//En caso contrario, se pone el valor 0
void slt(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        if(registers[rs1].value < registers[rs2].value){
            registers[rd].value = 0x00000001;
        }
        else{
            registers[rd].value = 0x00000000;
        }
        pc += 4;
    }
}

//Instrucción SLTI: si rs1 < valor inmediato, entonces se pone el valor 1 en rd.
//En caso contrario, se pone el valor 0
void slti(uint8_t rd, uint8_t rs1, int32_t imm_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        if(registers[rs1].value < imm_i){
            registers[rd].value = 0x00000001;
        }
        else{
            registers[rd].value = 0x00000000;
        }
        pc += 4;
    }
}

//Instrucción SLTIU: si rs1 < valor inmediato sin signo, entonces
//se pone el valor 1 en rd. En caso contrario, se pone el valor 0
void sltiu(uint8_t rd, uint8_t rs1, uint32_t imm_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        if(registers[rs1].value < imm_i){
            registers[rd].value = 0x00000001;
        }
        else{
            registers[rd].value = 0x00000000;
        }
        pc += 4;
    }
}

//Instrucción SLTU: si rs1 (sin signo) < rs2 (sin signo),
//entonces se pone el valor 1 en rd. En caso contrario,
//se pone el valor 0
void sltu(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        if((uint32_t) registers[rs1].value < (uint32_t) registers[rs2].value){
            registers[rd].value = 0x00000001;
        }
        else{
            registers[rd].value = 0x00000000;
        }
        pc += 4;
    }
}

//Instrucción SRL: corre a la derecha (rs2%32) todos los bytes de
//rs1, y almacena el resultado en rd
void srl(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t shiftValue = registers[rs2].value%32;
        registers[rd].value = registers[rs1].value>>shiftValue;
        pc += 4;
    }
}

//Instrucción SRLI: corre a la derecha (valor_inmediato%32)
//todos los bytes de rs1, y almacena el resultado en rd
void srli(uint8_t rd, uint8_t rs1, int32_t shamt_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int8_t shiftValue = shamt_i%32;
        registers[rd].value = registers[rs1].value>>shiftValue;
        pc += 4;
    }
}

//Instrucción SRA: corre a la derecha (rs2%32) todos los bytes de
//rs1, y almacena el resultado en rd
void sra(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t shiftValue = registers[rs2].value%32;
        registers[rd].value = registers[rs1].value>>shiftValue;
        pc += 4;
    }
}

//Instrucción SRAI: corre a la derecha (valor_inmediato%32)
//todos los bytes de rs1, y almacena el resultado en rd
void srai(uint8_t rd, uint8_t rs1, int32_t shamt_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        int32_t shiftValue = shamt_i%32;
        registers[rd].value = registers[rs1].value>>shiftValue;
        pc += 4;
    }
}

//sub instruction
void sub(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value - registers[rs2].value;
        pc += 4;
    }
}

//Instrucción XOR: se realiza la operación lógica XOR entre los valores de rs1 y rs2,
//luego se almacena el resultado en rd
void xor(uint8_t rd, uint8_t rs1, uint8_t rs2){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rs2 < 0 || rs2 > 31){
        fprintf(stderr, "The register %d does not exist", rs2);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value ^ registers[rs2].value;
        pc += 4;
    }
}

//Instrucción XORI: se realiza la operación lógica XOR entre el valor de rs1
//y un valor inmediato, luego se almacena el resultado en rd
void xori(uint8_t rd, uint8_t rs1, int32_t imm_i){
    if(rd < 0 || rd > 31){
        fprintf(stderr, "The register %d does not exist", rd);
    }
    else if(rs1 < 0 || rs1 > 31){
        fprintf(stderr, "The register %d does not exist", rs1);
    }
    else if(rd == 0){
        perror("The value of register x0 cannot be modified");
    }
    else{
        registers[rd].value = registers[rs1].value ^ imm_i;
        pc += 4;
    }
}

















#endif /* instructions_h */
