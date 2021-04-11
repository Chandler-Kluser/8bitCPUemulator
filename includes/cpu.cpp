#include <stdio.h>
#include <stdlib.h>

struct CPU
{
    Byte PC;    // Program Counter
    Byte A,B,I,M; // A, B, Instruction and Memory Address Registers

    void Reset(){
        PC = 0x00;
        A = B = I = M = 0x00;
    }

    void Execute ( unsigned char Cycles, Mem ){
        while (Cycles>0){
            
        }
    }
};