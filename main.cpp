// ==================================================
// ##        Ben Eater's CPU Emulator (v1.0)       ##
// ##                                              ##
// ##  Author: Chandler Klüser Chantre             ##
// ##  Date: 04/11/2021                            ##
// ==================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "includes/mem.cpp"
#include "includes/cpu.cpp"

using namespace std;

void checkCLK(){
    int a;
    cin>>a;
    if (a==0) {
        cout<<"zero!"<<endl;
    } else {
        cout<<a<<endl;
    }
}

int main(){
    int ExtClock = 0; // Generate an external clock counter
    CPU cpu;
    cpu.mem.Initialise();

    // TO DO: find a way to write memory from an hexadecimal file, then
    // import to the program and use it to write the memory

    // - Learn how does an hex file work
    // - Learn how to import an hex file to a C++ program
    // - Implement to the program, in order to have an argument when running the compiled emulator

    // TO DO: Implement the flags register and add the conditional instructions JEZ and JOC, add raise flag microinstruction when overflowing or zeroing the ALU

    // TO DO: Add mneumonic interpreter to write in the CPU terminal debugger (example 0001 0010 -->  LIA 2)

    // TO DO: add keypressed detection to make manual clocks or halt execution (see checkCLK function)

    cpu.mem.Write(0x0,0x0F); // LDA 15
    cpu.mem.Write(0x1,0x2E); // STA 14
    cpu.mem.Write(0x2,0x3E); // ADD 14
    cpu.mem.Write(0x3,0x2F); // STA 15
    cpu.mem.Write(0x4,0x82); // JMP 2
    cpu.mem.Write(0xF,0x01); // 15-> 0x01
    cpu.Reset( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    for (int i = 0; i < 5*5; i++)
    {
        cpu.Execute( ExtClock );
        if (i%5==0){
            cpu.Debug();
            cpu.mem.Debug();
        }
        ExtClock+=1;
    }
    return 0;
}