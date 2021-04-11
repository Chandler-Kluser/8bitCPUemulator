#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

struct CPU
{
    int Cycles = 0; // Catches the external Clock to do a Step per Clock cycle
    Byte PC;        // Program Counter
    Byte Step;      // 0-1-2-3-4 Instruction Step Counter
    Byte A,B,I,M;   // A, B, Instruction and Memory Address Registers

    void Reset(int ExtClock){
        PC = 0x00;         // Zeros the PC
        A = B = I = M = 0x00; // Zeros the registers
        Cycles = ExtClock; // Matches the External Clock with the Internal Clock Counter
    }

    void CPUExceptions(int ExtClock, Mem mem){
        if (Cycles!=ExtClock) throw std::invalid_argument("External Clock and Intern Clock CPU Counter must match.");
        if (PC>15) throw std::invalid_argument("Program Counter has exceeded its limit of 4 bits.");
        if (Step>5) throw std::invalid_argument("Step Counter must be greater or equal to 0 and Lesser then 6.");
        if (A>255||B>255||I>255) throw std::invalid_argument("A, B or I registers has exceeded its limit of 8 bits.");
        if (M>15) throw std::invalid_argument("M register has exceeded its limit of 4 bits.");
    }

    void FetchInstruction(){
        cout<<"The value of I register is: "<<hex<< (I>>0) <<endl;
        cout<<"The 4 MSBs of I register is: "<<hex<< (I>>4) << endl;
        cout<<"The 4 LSBs of I register is: "<<hex<< (I & 0x0F) << endl;
    }

    void Execute ( int ExtClock, Mem mem ){
        Step = 0x0; // Zerate the Step Counter
        CPUExceptions( ExtClock, mem ); // Raise some CPU Errors

        while (Step<5){
            switch (Step)
            {
            case 0x0:
                M = PC;          // CO + MI
                break;
            case 0x1:
                PC++;            // CE
                I = mem.read(M); // II + RO
                break;
            case 0x2:
                FetchInstruction();
                break;
            
            default:
                break;
            }
            Cycles++;
            Step++;
        }
    }
};