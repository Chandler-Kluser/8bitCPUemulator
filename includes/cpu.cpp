#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

struct CPU
{
    int Cycles = 0;     // Catches the external Clock to do a Step per Clock cycle
    Byte PC;            // Program Counter
    Byte Bus;           // 8-bit bus
    Byte Step;          // 0-1-2-3-4 Instruction Step Counter
    Byte A,B,I,M;       // A, B, Instruction and Memory Address Registers
    Mem mem;            // CPU Memory
    ByteDivider Inst;   // This is not a Real Hardware, This is only to keep in memory what instr the cpu has to parse

    void Debug(){
        cout<<"=================="<<endl;
        cout<<"##    A   | "<<hex<<(A>>0)<<"  ##"<<endl;
        cout<<"##    B   | "<<hex<<(B>>0)<<"  ##"<<endl;
        cout<<"##    I   | "<<hex<<(I>>0)<<"  ##"<<endl;
        cout<<"##    M   | "<<hex<<(M>>0)<<"  ##"<<endl;
        cout<<"##   RAM  | "<<hex<<(mem.Read(M)>>0)<<"  ##"<<endl;
        cout<<"##   Bus  | "<<hex<<(Bus>>0)<<"  ##"<<endl;
        cout<<"##   PC   | "<<hex<<(PC>>0)<<"  ##"<<endl;        
        cout<<"=================="<<endl;
        cout<<"|"<<endl;
        cout<<"\\-> Clock Cycle: "<<dec<<(Cycles>>0)<<endl;
    }

    void Reset(int ExtClock){
        PC = 0x00;         // Zeros the PC
        A = B = I = M = 0x00; // Zeros the registers
        Cycles = ExtClock; // Matches the External Clock with the Internal Clock Counter
        Step = 0; // Zerate the Step Counter
    }

    void CPUExceptions(int ExtClock){
        if (Cycles!=ExtClock) throw std::invalid_argument("External Clock and Intern Clock CPU Counter must match.");
        if (PC>15) throw std::invalid_argument("Program Counter has exceeded its limit of 4 bits.");
        if (Step>4) throw std::invalid_argument("Step Counter must be greater or equal to 0 and Lesser then 5.");
        if (A>255||B>255||I>255) throw std::invalid_argument("A, B or I registers has exceeded its limit of 8 bits.");
        if (M>15) throw std::invalid_argument("M register has exceeded its limit of 4 bits.");
    }

    ByteDivider FetchInstruction(){ // Separates the 4 MSBs of the 4 LSBs of the Byte given by I register
        ByteDivider a;
        a.MSB = (I>>4);     // Instruction OpCode ( 4 MSBs )
        a.LSB = (I & 0x0F); // Data ( 4 LSBs )
        return a;
    }

    void Parser02(){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            M = Inst.LSB; // IO + MI
            Bus = M; // Write Bus
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            A = Inst.LSB; // IO + AI
            Bus = A; // Write Bus
            break;
        case 0x2: // STA X - Store A Register in Memory
            M = Inst.LSB; // IO + MI
            Bus = M; // Write Bus
            break;
        case 0x3: // ADD X - Add in A Register
            M = Inst.LSB; // IO + MI
            Bus = M; // Write Bus
            break;
        case 0x4: // ADI X - Add Imediatelly in A Register
            B = Inst.LSB; // IO + BI
            Bus = B; // Write Bus
            break;
        case 0x7: // NOP - Does nothing
            Bus = 0; // Write Bus
            break;
        case 0x8: // JMP X - Jump PC to X Address
            PC = Inst.LSB; // J + IO
            Bus = PC;  // Write Bus
            break;
        default:
            break;
        }
    }

    void Parser03(){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            A = mem.Read(M); // RO + AI
            Bus = A; // Write Bus
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            Bus = 0; // Write Bus
            break;    
        case 0x2: // STA X - Store A Register in Memory
            mem.Write(M,A); // AO + RI
            Bus = A; // Write Bus
            break;
        case 0x3: // ADD X - Add in A Register
            B = mem.Read(M); // RO + BI
            Bus = B; // Write Bus
            break;
        case 0x4: // ADI X - Add Imediatelly in A Register
            // TO DO: verify overflow settings A>255
            // TO DO: add carry to the flags register
            A = A + B; // SumO + AI
            Bus = A; // Write Bus
            break;
        case 0x7: // NOP - Does nothing
            Bus = 0; // Write Bus
            break;
        case 0x8: // JMP X - Jump PC to X Address
            Bus = 0; // Write Bus
            break;
        default:
            break;
        }
    }

    void Parser04(){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            Bus = 0; // Write Bus
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            Bus = 0; // Write Bus
            break;
        case 0x2: // STA X - Store A Register in Memory
            Bus = 0; // Write Bus
            break;
        case 0x3: // ADD X - Add in A Register
            // TO DO: verify overflow settings A>255
            A = A + B; // SumO + AI
            Bus = A; // Write Bus
            break;
        case 0x4: // ADI X - Add Imediatelly in A Register
            Bus = 0; // Write Bus
            break;
        case 0x7: // NOP - Does nothing
            Bus = 0; // Write Bus
            break;
        case 0x8: // JMP X - Jump PC to X Address
            Bus = 0; // Write Bus
            break;
        default:
            break;
        }
    }

    void Execute ( int ExtClock ){
        CPUExceptions( ExtClock ); // Raise some CPU Errors
        switch (Step)
            {
            case 0:
                M = PC;          // CO + MI
                Bus = PC;
                break;
            case 1:
                PC++;            // CE --> Increment Program Counter
                I = mem.Read(M); // II + RO
                Bus = I;
                break;
            case 2:
                Inst = FetchInstruction();
                Parser02();
                break;
            case 3:
                Parser03();
                break;
            case 4:
                Parser04();
                Step = -1;      // -1 will be added to 1 in order to restart to Step 0 again
                break;
            default:
                break;
            }
            Cycles++;
            Step++;
    }
};