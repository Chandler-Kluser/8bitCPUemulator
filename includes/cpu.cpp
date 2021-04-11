#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

struct CPU
{
    int Cycles = 0; // Catches the external Clock to do a Step per Clock cycle
    Byte PC;        // Program Counter
    Byte Step;      // 0-1-2-3-4 Instruction Step Counter
    Byte A,B,I,M;   // A, B, Instruction and Memory Address Registers

    void Reset(int ExtClock){
        PC = 0x00;
        A = B = I = M = 0x00;
        Cycles = ExtClock;
    }

    void Execute ( int ExtClock, Mem mem ){
        Step = 0x0; // Zerate the Step Counter
        if (Cycles!=ExtClock) throw std::invalid_argument("External Clock and Intern Clock CPU Counter must match.");
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
            Cycles++;
            Step++;
        }
    }
};