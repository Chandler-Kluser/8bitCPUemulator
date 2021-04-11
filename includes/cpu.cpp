#include <stdio.h>
#include <stdlib.h>

struct CPU
{
    Byte PC;    // Program Counter
    Byte Step;  // 0-1-2-3-4 Instruction Step Counter
    Byte A,B,I,M; // A, B, Instruction and Memory Address Registers

    void Reset(){
        PC = 0x00;
        A = B = I = M = 0x00;
    }

    Byte Fetch( Mem mem ){
        return 0x00;
    }

    void Execute ( Mem mem ){
        Step = 0x0; // Zerate the Step Counter
        Byte Instruction = Fetch( mem ); // Fetchs The Instruction
        while (Step<5){
            switch (Step)
            {
            case 0x0:
                // Do something
                break;
            case 0x1:
                // Do something else
                break;
            
            default:
                break;
            }
            Step++;
        }
    }
};