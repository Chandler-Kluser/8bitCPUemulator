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
    cpu.mem.Write(0x0,0x0F);
    cpu.mem.Write(0x1,0x2E);
    cpu.mem.Write(0x2,0x3E);
    cpu.mem.Write(0x3,0x2F);
    cpu.mem.Write(0xF,0x01);
    cpu.Reset( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    cpu.Execute( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    ExtClock+=5;
    cpu.Execute( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    ExtClock+=5;
    cpu.Execute( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    ExtClock+=5;
    cpu.Execute( ExtClock );
    cpu.Debug();
    cpu.mem.Debug();
    return 0;
}