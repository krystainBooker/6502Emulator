#include <iostream>
#include <M6502Emulator.h>

using namespace std;

int main()
{
    cout << "Internal screaming";
    M6502::Memory memory;
    M6502::CPU cpu;

    //cpu.Reset(memory);

    //start - inline program
    //memory[0xFFFC] = CPU::LDA_ZP;
    //memory[0xFFFD] = 0x42;
    //memory[0x0042] = 0x84;
    //end - inline program

    //cpu.Execute(3, memory);

    return 0;
}