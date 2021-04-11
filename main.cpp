// ==================================================
// ##        Ben Eater's CPU Emulator (v1.0)       ##
// ##                                              ##
// ##  Author: Chandler Klüser Chantre             ##
// ##  Date: 04/10/2021                            ##
// ==================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "includes/mem.cpp"
#include "includes/cpu.cpp"

using namespace std;

int main(){
    Mem mem;
    CPU cpu;
    mem.Data[0] = 0x0F;
    cpu.Reset();
    cout<<mem.read(0)<<endl;
    return 0;
}