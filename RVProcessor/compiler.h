//
//  compiler.h
//  miprocesador
//
//  Created by Guillermo Nájera Lavid on 05/05/2022.
//

#ifndef compiler_h
#define compiler_h
#include <string.h>

void compile(FILE *file){
    int i = 0, j, x, y, z, separators;
    int* programInHex;
    programInHex = malloc(sizeof(int)*5);
    char line[30];
    while (fgets(line, 30, file)) {
        j = 0;
        x = 0;
        y = 0;
        z = 0;
        separators = 0;
        char arg1[3], arg2[3], arg3[3];
        while(line[j] != ')') {
            if (line[j] == '(') {
                separators++;
                j++;
                continue;
            }
            if (line[j] == ',') {
                separators++;
                j++;
                continue;
            }
            switch (separators) {
                case 1:
                    arg1[x] = line[j];
                    x++;
                    break;
                case 2:
                    arg2[y] = line[j];
                    y++;
                    break;
                case 3:
                    arg3[z] = line[j];
                    z++;
                    break;
            }
            j++;
        }
        arg1[x] = '\0';
        arg2[y] = '\0';
        arg3[z] = '\0';
        if (strstr(line, "add(")) {
            *(programInHex + i) = 0x1;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "addi(")) {
            *(programInHex + i) = 0x2;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "and(")) {
            *(programInHex + i) = 0x3;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "andi(")) {
            *(programInHex + i) = 0x4;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "auipc(")) {
            *(programInHex + i) = 0x5;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2)&0x000000FF;
            *(programInHex + (i+3)) = -1;
        }
        else if (strstr(line, "beq(")) {
            *(programInHex + i) = 0x6;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "bge(")) {
            *(programInHex + i) = 0x7;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "bgeu(")) {
            *(programInHex + i) = 0x8;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "blt(")) {
            *(programInHex + i) = 0x9;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "bltu(")) {
            *(programInHex + i) = 0xA;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "bne(")) {
            *(programInHex + i) = 0xB;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "jal(")) {
            *(programInHex + i) = 0xC;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2)&0x000000FF;
            *(programInHex + (i+3)) = -1;
        }
        else if (strstr(line, "jalr(")) {
            *(programInHex + i) = 0xD;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "lb(")) {
            *(programInHex + i) = 0xE;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "lbu(")) {
            *(programInHex + i) = 0xF;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "lh(")) {
            *(programInHex + i) = 0x10;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "lhu(")) {
            *(programInHex + i) = 0x11;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "lui(")) {
            *(programInHex + i) = 0x12;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2)&0x000000FF;
            *(programInHex + (i+3)) = -1;
        }
        else if (strstr(line, "lw(")) {
            *(programInHex + i) = 0x13;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "or(")) {
            *(programInHex + i) = 0x14;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "ori(")) {
            *(programInHex + i) = 0x15;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sb(")) {
            *(programInHex + i) = 0x16;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sh(")) {
            *(programInHex + i) = 0x17;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sw(")) {
            *(programInHex + i) = 0x18;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sll(")) {
            *(programInHex + i) = 0x19;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "slli(")) {
            *(programInHex + i) = 0x1A;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "slt(")) {
            *(programInHex + i) = 0x1B;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "slti(")) {
            *(programInHex + i) = 0x1C;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sltiu(")) {
            *(programInHex + i) = 0x1D;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sltu(")) {
            *(programInHex + i) = 0x1E;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "sra(")) {
            *(programInHex + i) = 0x1F;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "srai(")) {
            *(programInHex + i) = 0x20;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "srl(")) {
            *(programInHex + i) = 0x21;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "srli(")) {
            *(programInHex + i) = 0x22;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
        else if (strstr(line, "sub(")) {
            *(programInHex + i) = 0x23;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "xor(")) {
            *(programInHex + i) = 0x24;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3);
        }
        else if (strstr(line, "xori(")) {
            *(programInHex + i) = 0x25;
            *(programInHex + (i+1)) = atoi(arg1);
            *(programInHex + (i+2)) = atoi(arg2);
            *(programInHex + (i+3)) = atoi(arg3)&0x000000FF;
        }
       
        
        i += 4;
    }
    *(programInHex + i) = -2;
    memoryPool[i] = -2;
    for (int i = 0; programInHex[i] != -2; i += 4) {
        memoryPool[i] = programInHex[i];
        memoryPool[i+1] = programInHex[i+1];
        memoryPool[i+2] = programInHex[i+2];
        memoryPool[i+3] = programInHex[i+3];
        
    }
}

#endif /* compiler_h */
