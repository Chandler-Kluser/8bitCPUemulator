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
    // 32 Words (02 bytes) of memory
    static constexpr unsigned char MAX_MEM = 32;
    Word Data[MAX_MEM];

    void Debug(){ // Prints out all memories
        cout<<hex<<"========================================================================================="<<endl;
        for (int i = 0; i < 4; i++)
        {
            cout<<"## "<<i<<"-> "<<Data[i];
            for (int j = 4; j<MAX_MEM; j+=4){
                cout<<" || "<<i+j<<"-> "<<Data[i+j]<<" ";
            }
            cout<<"##"<<endl;
        }
        cout<<"========================================================================================="<<endl;
    }

    Word Read(unsigned char address){
        if (address>MAX_MEM) throw std::invalid_argument("Address of the RAM Memory must have 5 bits.");
        
        return Data[address];
    }

    void Write(unsigned char address , Word value=0x00){
        if (address>MAX_MEM) throw std::invalid_argument("Address of the RAM Memory must have 5 bits.");
        
        Data[address] = value;
    }

    void Initialise(){ // Zeros every word in memory
        for (int i = 0; i < MAX_MEM; i++)
        {
            Data[i]=0x00;
        }
    }
};