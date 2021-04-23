// ==================================================
// ##         Chandler's CPU Emulator (v1.0)       ##
// ##                                              ##
// ##  Author: Chandler Klüser Chantre             ##
// ##  Date: 04/19/2021                            ##
// ==================================================

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "includes/mem.cpp"
#include "includes/cpu.cpp"

using namespace std;

void clrscr(){ // clears the screen
    cout << "\033[2J\033[1;1H";
}

int IntDialog(string str,bool show = 1){ // test console input dialog
    int a;
    if (show){
        cout<<endl<<str<<endl;
    }
    cin>>a;
    return a;
}

int main(int argc, char** argv){
    // Read HEX file given as argument
    // ifstream input("test.hex", ios::binary );
    ifstream input(argv[1], ios::binary );
    // copies all data into buffer
    vector<unsigned char> buffer(istreambuf_iterator<char>(input), {});

    int ExtClock = 0; // Generate an external clock counter
    CPU cpu;
    cpu.mem.Initialise();

    // =========================== TO DO LIST ======================================

    // TO DO: Add keypressed detection to make manual clocks or halt execution (see checkCLK function)

    // TO DO: Add console print functionality to print hex numbers lesser than 0x10
    // to print one non significant digit.
    // Example:
    // How it actually is:  ||   How I wish it should be:
    //       1F             ||            1F
    //        A             ||            0A
    //        3             ||            03
    //       FF             ||            FF

    // TO DO: Print the Instruction Argument as hex not in dec
    // Example:
    // How it actually is:  ||   How I wish it should be:
    //       10             ||            0A
    //       16             ||            FF

    // TO DO: Add more args to the main function and a parser for those, suggestions:
    // -h --help : display some help, argument entering
    // -dm --dump-memory <txtfile> : dump memory in a txt file in every clock cycle
    // -di --dump-instr <txtfile> : dump instructions executed in a txt file

    // TO DO: Develop a quick assembler for this CPU (assembly to hex)

    // TO DO: Develop a quick disassembler for this CPU (hex to assembly)

    // TO DO: Make a brief GUI with Qt for the emulator

    // =============================================================================

    // Write Memory from HEX file
    for (int i=0;i<0x20;i++){
        cpu.mem.Write(i,int(buffer[i]));
    }
    cpu.Reset( ExtClock );
    int count=0;
    unsigned char a=1;
    while(1)
    {
        if (count%6==0)
        {
            if (cpu.Cycles>0) a = IntDialog("Show next instruction? (1: yes /0: no /-1: exit)");
            if (a==1){
                clrscr();
                cpu.mem.Debug();
                cpu.Debug();
            }
            else if (a!=0) break;
        }
        count++;
        cpu.Execute( ExtClock );
        ExtClock+=1;
    }
    return 0;
}