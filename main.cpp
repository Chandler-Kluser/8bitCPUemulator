// ==================================================
// ##        Ben Eater's CPU Emulator (v1.0)       ##
// ##                                              ##
// ##  Author: Chandler Klüser Chantre             ##
// ##  Date: 04/10/2021                            ##
// ==================================================

#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

struct Mem
{
    static constexpr unsigned char MAX_MEM = 16;
    Word Data[MAX_MEM];
};


struct CPU
{
    Byte PC;    // Program Counter
    Byte A,B,I,M; // A, B, Instruction and Memory Address Registers

    void Reset(){
        PC = 0x00;
    }

    void Execute ( unsigned char Cycles, Mem ){
        while (Cycles>0){
            
        }
    }
};

int main(){
    Mem mem;
    CPU cpu;
    cpu.Reset();
    return 0;
}