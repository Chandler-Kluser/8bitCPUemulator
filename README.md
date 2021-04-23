# Chandler's 8-bit CPU C++ Emulator

Author: Chandler Klüser (chandler.kluser@gmail.com)

## Requirements:

- g++ Installed
- A HEX Editor (or a Text Editor + Assembler) to make your programs

## Installation:

- Download this repository;

- Compile the program:
`g++ main.cpp -o cpu.bin`

## How to use

- Write a Program in Assembly and use an Assembler or write directly the hex file

- Run your program in the Emulator:
`./cpu.bin yourhexfile.hex`

## Instructions

Instruction | Mneumonic | Description
----|-------|-------------------------
000 | LDA X | Loads to A the RAM data located in Address X
001 | LIA X | Loades to A the X data directly (X must have 5-bit length)
010 | STA X | Stores in A the RAM data located in Address X
011 | SWP X | Swaps Registers A and B using the X RAM Address as Auxiliar Memory
100 | JMP X | Jumps the Program Counter to the X Position (5-bit)
101 | JEZ X | If ALU==0, Jumps the PC to the X Position (5-bit)
110 | ADD X | Adds Register A with the RAM data located in Address X
111 | SUB X | Subtracts Register A with the RAM data located in Address X

```
   AAA BBBBB
   \-/ \---/
    |    \-----> Argument (5-bit word)
    \----------> OpCode (3-bit word)

Example:
JMP 13 --->  010 01101
             \-/ \---/
              |    \-----> Argument (5-bit word)
              \----------> OpCode (3-bit word)
```

## CPU Architecture

```
                     /--------------/-----------------/--------------------\
                     |              |                 |                    | 
                 Register A ------ ALU --------- Register B                |     
                     ||            ||                ||                    |   
                     || 8 bit      || 8 bit          || 8 bit              |     
                     ||            ||                ||                    |       
 Bus ============================================================ (8-bit)  |       
             ||                  ||              \/ || /\                  |       
             || 5 bit            || 8 bit     8 bit || 5 LSB's             |         
             ||                  ||              \/ || /\                  |       
        Memory Register     RAM (32x8-bit)   Instruction Register          |      
              |                  |                  || \/                  |      
              |                  |                  || 3 MSB's             |        
              |                  |                  || \/                  |        
              \------------------\----------------DECODER------------------/
```

## Decoder Details

```
RAM >> 32 8-bit Addresses (32 Bytes)
Control Unit (DECODER) with 3-bit OpCode

------------------
|                |-> AIn,BIn,AOut,BOut (Registers Control)
|                |-> CounterO,CounterIncrement,CounterJump (PC Control)
|    DECODER     |-> MI,RI,RO (Memory Address and RAM Control)
|                |-> AluOut, SB* (Alu Control)
|                |-> IIn,IOut (Instruction Register Control)
|                |-> FIn,FOut (Register Flag Control - EqualZero)
------------------
              |    \___________________________________________________/
3 MSBs   >----/         |
(OpCode)      |         \---> 15 Control Signals
              |               (DECODER must have at least 4-bit memory)
    EZ   >----/
(Flag Register)

*SB --> SIGNAL NOT A (NA) + NOT OUT (NO) IN ALU (HARDWARE IMPLEMENTED)
```

## Decoder Signals Table

```
EZ Flag Register (Not a Control Signal) >----------------------\
                                                               |
#===============================================================#
# Step | Instr. |AI|AO|BI|BO|CO|CI|CJ|MI|RI|RO|SO|SB|II|IO|FI|EZ#
#===============================================================#
#   0  |  ----  |  |  |  |  |CO|  |  |MI|  |  |  |  |  |  |  |XX#
#   1  |  ----  |  |  |  |  |  |CI|  |  |  |RO|  |  |II|  |  |XX#
#===============================================================#
#   2  |  LDA X |  |  |  |  |  |  |  |MI|  |  |  |  |  |IO|  |XX#
#   3  |  LDA X |AI|  |  |  |  |  |  |  |  |RO|  |  |  |  |  |XX#
#   4  |  LDA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   5  |  LDA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
#   2  |  LIA X |AI|  |  |  |  |  |  |  |  |  |  |  |  |IO|  |XX#
#   3  |  LIA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   4  |  LIA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   5  |  LIA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
#   2  |  STA X |  |  |  |  |  |  |  |MI|  |  |  |  |  |IO|  |XX#
#   3  |  STA X |  |AO|  |  |  |  |  |  |RI|  |  |  |  |  |  |XX#
#   4  |  STA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   5  |  STA X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
#   2  |  SWP X |  |  |  |  |  |  |  |MI|  |  |  |  |  |IO|  |XX#
#   3  |  SWP X |AO|  |  |  |  |  |  |  |RI|  |  |  |  |  |  |XX#
#   4  |  SWP X |  |AI|  |BO|  |  |  |  |  |  |  |  |  |  |  |XX#
#   5  |  SWP X |  |  |BI|  |  |  |  |  |  |RO|  |  |  |  |  |XX#
#===============================================================#
# Step | Instr. |AI|AO|BI|BO|CO|CI|CJ|MI|RI|RO|SO|SB|II|IO|FI|EZ#
#===============================================================#
#   2  |  JMP X |  |  |  |  |  |  |CJ|  |  |  |  |  |  |IO|  |XX#
#   3  |  JMP X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   4  |  JMP X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   5  |  JMP X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
#   2  |  JEZ X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  #
#------+--------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--#
#   2  |  JEZ X |  |  |  |  |  |  |CJ|  |  |  |  |  |  |IO|  |EZ#
#------+--------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--#
#   3  |  JEZ X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   4  |  JEZ X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#   5  |  JEZ X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
#   2  |  ADD X |  |  |  |  |  |  |  |MI|  |  |  |  |  |IO|  |XX#
#   3  |  ADD X |  |BI|  |  |  |  |  |  |  |RO|  |  |  |  |  |XX#
#   4  |  ADD X |AI|  |  |  |  |  |  |  |  |  |SO|  |  |  |FI|XX#
#   5  |  ADD X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
#   2  |  SUB X |  |  |  |  |  |  |  |MI|  |  |  |  |  |IO|  |XX#
#   3  |  SUB X |  |BI|  |  |  |  |  |  |  |RO|  |  |  |  |  |XX#
#   4  |  SUB X |AI|  |  |  |  |  |  |  |  |  |SO|SB|  |  |FI|XX#
#   5  |  SUB X |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |XX#
#===============================================================#
```