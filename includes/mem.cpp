#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

struct Mem
{
    // 16 Words (02 bytes) of memory
    static constexpr unsigned char MAX_MEM = 16;
    Word Data[MAX_MEM];

    Word read(unsigned char address){
        // TO DO: Add verification if the 
        // value of the address is greater
        // than MAX_MEM
        return Data[address];
    }

    void Initialise(){ // Zeros every word in memory
        for (int i = 0; i < MAX_MEM; i++)
        {
            Data[i]=0x00;
        }
    }
};