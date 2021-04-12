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

int main(){
    int ExtClock = 0; // Generate an external clock counter
    CPU cpu;
    cpu.mem.Initialise();

    // TO DO: find a way to write memory from an hexadecimal file, then
    // import to the program and use it to write the memory

    // - Learn how does an hex file work
    // - Learn how to import an hex file to a C++ program
    // - Implement to the program, in order to have an argument when running the compiled emulator

    // TO DO: disassembly the cpu::Execute function from 5 Steps and make it dependable of the external
    // clock in every step, not only 5 to 5 steps

    // TO DO: implement 8 bit bus (Byte) and add It to the struct CPU and add the values to the bus in
    // every instruction that involves using it.

    cpu.mem.Write(0x0,0x0F); // LDA 15
    cpu.mem.Write(0x1,0x2E); // STA 14
    cpu.mem.Write(0x2,0x3E); // ADD 14
    cpu.mem.Write(0x3,0x2F); // STA 15
    cpu.mem.Write(0x4,0x82); // JMP 2
    cpu.mem.Write(0xF,0x01); // 15-> 0x01
    cpu.Reset( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    for (int i = 0; i < 10; i++)
    {
        cpu.Execute( ExtClock );
        cpu.Debug();
        cpu.mem.Debug();
        ExtClock+=5;
    }
    return 0;
}