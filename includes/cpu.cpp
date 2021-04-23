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
    Byte Step;          // 0-1-2-3-4-5 Instruction Step Counter
    Byte A,B,I,M;       // A, B, Instruction and Memory Address Registers
    Mem mem;            // CPU Memory
    ByteDivider Inst;   // This is not a Real Hardware, This is only to keep in memory what instr the cpu has to parse
    bool EZ;            // EZ Flag Register

    string PrintInstruction(ByteDivider Inst){
        string a;
        switch (Inst.MSB)
        {
        case 0: a = "LDA "; break;
        case 1: a = "LIA "; break;
        case 2: a = "STA "; break;
        case 3: a = "SWP "; break;
        case 4: a = "JMP "; break;
        case 5: a = "JEZ "; break;
        case 6: a = "ADD "; break;
        case 7: a = "SUB "; break;
        default: break;
        }
        a = a+to_string(Inst.LSB);
        return a;
    }

    void Debug(bool ShowInstruction = true){
        if (ShowInstruction) cout<<"Instruction: "<<PrintInstruction(Inst)<<endl;
        cout<<"=================="<<endl;
        cout<<"##    A   | "<<hex<<(A>>0)<<"  ##"<<endl;
        cout<<"##    B   | "<<hex<<(B>>0)<<"  ##"<<endl;
        cout<<"##    I   | "<<hex<<(I>>0)<<"  ##"<<endl;
        cout<<"##    M   | "<<hex<<(M>>0)<<"  ##"<<endl;
        cout<<"##   RAM  | "<<hex<<(mem.Read(M)>>0)<<"  ##"<<endl;
        cout<<"##   Bus  | "<<hex<<(Bus>>0)<<"  ##"<<endl;
        cout<<"##   PC   | "<<hex<<(PC>>0)<<"  ##"<<endl;
        cout<<"##   EZ   | "<<hex<<(EZ>>0)<<"  ##"<<endl;        
        cout<<"=================="<<endl;
        cout<<"|"<<endl;
        cout<<"\\-> Clock Cycle: "<<dec<<(Cycles>>0)<<endl;
    }

    void Reset(int ExtClock){
        PC = 0;            // Zeros the PC
        A = B = I = M = 0; // Zeros the registers
        Cycles = ExtClock; // Matches the External Clock with the Internal Clock Counter
        Step = 0;          // Zerate the Step Counter
        EZ = 0;            // Zerate the EZ Flag Register
    }

    void CPUExceptions(int ExtClock){
        if (Cycles!=ExtClock) throw std::invalid_argument("External Clock and Intern Clock CPU Counter must match.");
        if (PC>31) throw std::invalid_argument("Program Counter has exceeded its limit of 5 bits.");
        if (Step>5) throw std::invalid_argument("Step Counter must be greater or equal to 0 and Lesser then 6.");
        if (A>255||B>255||I>255) throw std::invalid_argument("A, B or I registers has exceeded its limit of 8 bits.");
        if (M>31) throw std::invalid_argument("M register has exceeded its limit of 5 bits.");
    }

    ByteDivider FetchInstruction(){ // Separates the 3 MSBs of the 5 LSBs of the Byte given by I register
        ByteDivider a;
        a.MSB = (I>>5);     // Instruction OpCode ( 3 MSBs )
        a.LSB = (I & 0x1F); // Data ( 5 LSBs )
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
        case 0x3: // SWP X - Swap A and B Registers Using Memory Address X
            M = Inst.LSB; // IO + MI
            Bus = M; // Write Bus
            break;
        case 0x4: // JMP X - Jump to Instruction of X Address
            PC = Inst.LSB; // J + IO
            Bus = PC;  // Write Bus
            break;
        case 0x5: // JEZ X - Jump to Instruction of X Address, if EZ Flag is risen
            if (EZ) { // if the Zero in ALU Flag is risen...
                PC = Inst.LSB; // J + IO
                Bus = PC;  // Write Bus
            }
            break;
        case 0x6: // ADD X - ADD data located in X memory to A register and save there
            M = Inst.LSB; // IO + MI
            Bus = M; // Write Bus
            break;
        case 0x7: // SUB X - SUBTRACT data located in X memory from A register and save there
            M = Inst.LSB; // IO + MI
            Bus = M; // Write Bus
            break;
        default:
            break;
        }
    }

    void Parser03(){
        switch (Inst.MSB)
        {
        case 0x0: // LDA X - Load A Register
            A = mem.Read(I); // AI + RO
            Bus = A; // Write Bus
            break;
        case 0x1: // LIA X - Load Imediatelly A Register
            Bus = 0; // Write Bus
            break;
        case 0x2: // STA X - Store A Register in Memory
            mem.Write(M,A); // AO + RI
            Bus = A; // Write Bus
            break;
        case 0x3: // SWP X - Swap A and B Registers Using Memory Address X
            mem.Write(M,A); // AO + RI
            Bus = A; // Write Bus
            break;
        case 0x4: // JMP X - Jump to Instruction of X Address
            Bus = 0; // Write Bus
            break;
        case 0x5: // JEZ X - Jump to Instruction of X Address, if EZ Flag is risen
            Bus = 0; // Write Bus
            break;
        case 0x6: // ADD X - ADD data located in X memory to A register and save there
            B = mem.Read(M); // BI + RO
            Bus = B; // Write Bus
            break;
        case 0x7: // SUB X - SUBTRACT data located in X memory from A register and save there
            B = mem.Read(M); // BI + RO
            Bus = B; // Write Bus
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
        case 0x3: // SWP X - Swap A and B Registers Using Memory Address X
            A = B; // AI + BO
            Bus = A; // Write Bus
            break;
        case 0x4: // JMP X - Jump to Instruction of X Address
            Bus = 0; // Write Bus
            break;
        case 0x5: // JEZ X - Jump to Instruction of X Address, if EZ Flag is risen
            Bus = 0; // Write Bus
            break;
        case 0x6: // ADD X - ADD data located in X memory to A register and save there
            if (A+B>255){ // overflow
                A = A + B - 255; // AI + SO
                // Raise Jump On Carry Flag Here, If available
            } else {
                A = A + B; // AI + SO
            }
            if (A==0) EZ = 1; else EZ = 0; // FI
            Bus = A; // Write Bus
            break;
        case 0x7: // SUB X - SUBTRACT data located in X memory from A register and save there
            // TO DO: convert B to two's complement and bitwise add with A
            if (A-B<256){ 
                A = A - B + 256; // AI + SO + SB
                // TO DO: Make A return in two's complement representation in debug mode    
            } else {
                if (A - B < 0) {// overflow
                    // Raise Jump On Carry Flag Here, If available
                }
                A = A - B; // AI + SO + SB
            }
            if (A==0) EZ = 1; else EZ = 0; // FI
            Bus = A; // Write Bus
            break;
        default:
            break;
        }
    }

    void Parser05(){
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
        case 0x3: // SWP X - Swap A and B Registers Using Memory Address X
            B = mem.Read(M); // BI + RO
            Bus = B; // Write Bus
            break;
        case 0x4: // JMP X - Jump to Instruction of X Address
            Bus = 0; // Write Bus
            break;
        case 0x5: // JEZ X - Jump to Instruction of X Address, if EZ Flag is risen
            Bus = 0; // Write Bus
            break;
        case 0x6: // ADD X - ADD data located in X memory to A register and save there
            Bus = 0; // Write Bus
            break;
        case 0x7: // SUB X - SUBTRACT data located in X memory from A register and save there
            Bus = 0; // Write Bus
            break;
        default:
            break;
        }
    }

    void Execute ( int ExtClock ){
        CPUExceptions( ExtClock ); // Raise some CPU Errors
        Inst = FetchInstruction();
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
                // Inst = FetchInstruction(); // Actually (in real HW) it is executed in the 3rd Step
                Parser02();
                break;
            case 3:
                Parser03();
                break;
            case 4:
                Parser04();
                break;
            case 5:
                Parser05();
                Step = -1;      // -1 will be added to 1 in order to restart to Step 0 again
                break;
            default:
                break;
            }
            Cycles++;
            Step++;
    }
};