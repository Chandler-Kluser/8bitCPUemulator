#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

struct Mem
{
    // 16 Words (02 bytes) of memory
    static constexpr unsigned char MAX_MEM = 15;
    Word Data[MAX_MEM];

    Word read(unsigned char address){
        if (address>MAX_MEM) throw std::invalid_argument("Address of the RAM Memory must have 4 bits.");
        
        return Data[address];
    }

    void write(unsigned char address , Word value=0x00){
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