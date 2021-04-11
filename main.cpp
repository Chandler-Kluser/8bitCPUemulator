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
    Mem mem;
    mem.Initialise();
    mem.write(0,0xF2);
    CPU cpu;
    cpu.Reset( ExtClock );
    cpu.Execute( ExtClock, mem );
    return 0;
}