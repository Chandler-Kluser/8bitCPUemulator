// ==================================================
// ##        Ben Eater's CPU Emulator (v1.0)       ##
// ##                                              ##
// ##  Author: Chandler Klüser Chantre             ##
// ##  Date: 04/10/2021                            ##
// ==================================================

#include <stdio.h>
#include <stdlib.h>
#include "includes/mem.cpp"
#include "includes/cpu.cpp"

int main(){
    Mem mem;
    CPU cpu;
    cpu.Reset();
    return 0;
}