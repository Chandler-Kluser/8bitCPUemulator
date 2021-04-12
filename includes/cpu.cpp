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
    Mem mem;        // CPU Memory

    void Debug(){
        cout<<"=================="<<endl;
        cout<<"##    A   | "<<hex<<(A>>0)<<"  ##"<<endl;
        cout<<"##    B   | "<<hex<<(B>>0)<<"  ##"<<endl;
        cout<<"##    I   | "<<hex<<(I>>0)<<"  ##"<<endl;
        cout<<"##    M   | "<<hex<<(M>>0)<<"  ##"<<endl;
        cout<<"##   PC   | "<<hex<<(PC>>0)<<"  ##"<<endl;        
        cout<<"=================="<<endl;
        cout<<"|"<<endl;
        cout<<"\\-> Cycles: "<<dec<<(Cycles>>0)<<endl;
    }

    void Reset(int ExtClock){
        PC = 0x00;         // Zeros the PC
        A = B = I = M = 0x00; // Zeros the registers
        Cycles = ExtClock; // Matches the External Clock with the Internal Clock Counter
    }

    void CPUExceptions(int ExtClock){
        if (Cycles!=ExtClock) throw std::invalid_argument("External Clock and Intern Clock CPU Counter must match.");
        if (PC>15) throw std::invalid_argument("Program Counter has exceeded its limit of 4 bits.");
        if (Step>5) throw std::invalid_argument("Step Counter must be greater or equal to 0 and Lesser then 6.");
        if (A>255||B>255||I>255) throw std::invalid_argument("A, B or I registers has exceeded its limit of 8 bits.");
        if (M>15) throw std::invalid_argument("M register has exceeded its limit of 4 bits.");
    }

    ByteDivider FetchInstruction(){ // Separates the 4 MSBs of the 4 LSBs of the Byte given by I register
        ByteDivider a;
        a.MSB = (I>>4);     // Instruction OpCode ( 4 MSBs )
        a.LSB = (I & 0x0F); // Data ( 4 LSBs )
        return a;
    }

    void Parser02(ByteDivider Inst){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            M = Inst.LSB; // IO + MI
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            A = Inst.LSB; // IO + AI
            break;
        case 0x2: // STA X - Store A Register in Memory
            M = Inst.LSB; // IO + MI
            break;
        case 0x3: // ADD X - Add in A Register
            M = Inst.LSB; // IO + MI
            break;
        default:
            break;
        }
    }

    void Parser03(ByteDivider Inst){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            A = mem.Read(M); // RO + AI
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            break;    
        case 0x2: // STA X - Store A Register in Memory
            mem.Write(M,A); // AO + RI
            break;
        case 0x3: // ADD X - Add in A Register
            B = mem.Read(M); // RO + BI
            break;
        default:
            break;
        }
    }

    void Parser04(ByteDivider Inst){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            break;
        case 0x2: // STA X - Store A Register in Memory
            break;
        case 0x3: // ADD X - Add in A Register
            A = A + B; // SumO + AI
            break;
        default:
            break;
        }
    }

    void Execute ( int ExtClock ){
        Step = 0x0; // Zerate the Step Counter
        CPUExceptions( ExtClock ); // Raise some CPU Errors
        ByteDivider Inst;
        while (Step<5){
            switch (Step)
            {
            case 0x0:
                M = PC;          // CO + MI
                break;
            case 0x1:
                PC++;            // CE
                I = mem.Read(M); // II + RO
                break;
            case 0x2:
                Inst = FetchInstruction();
                Parser02(Inst);
                break;
            case 0x3:
                Parser03(Inst);
                break;
            case 0x4:
                Parser04(Inst);
                break;
            
            default:
                break;
            }
            Cycles++;
            Step++;
        }
    }
};