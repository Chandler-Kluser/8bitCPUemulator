#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

using Byte = unsigned char;
using Word = unsigned short;

struct ByteDivider{
    Byte MSB;
    Byte LSB;
};

struct Mem
{
    // 16 Words (02 bytes) of memory
    static constexpr unsigned char MAX_MEM = 16;
    Word Data[MAX_MEM];

    void Debug(){ // Prints out all memories
        cout<<"======================"<<endl;
        for (int i = 0; i < 8; i++)
        {
            cout<<"## "<<hex<<i<<"-> "<<Data[i]<<" || "
            <<hex<<i+8<<"-> "<<Data[i+8]<<" ##"<<endl;
        }
        cout<<"======================"<<endl;
    }

    Word Read(unsigned char address){
        if (address>MAX_MEM) throw std::invalid_argument("Address of the RAM Memory must have 4 bits.");
        
        return Data[address];
    }

    void Write(unsigned char address , Word value=0x00){
        if (address>MAX_MEM) throw std::invalid_argument("Address of the RAM Memory must have 4 bits.");
        
        Data[address] = value;
    }

    void Initialise(){ // Zeros every word in memory
        for (int i = 0; i < MAX_MEM; i++)
        {
            Data[i]=0x00;
        }
    }
};