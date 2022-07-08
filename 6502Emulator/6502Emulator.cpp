// 6502Emulator.cpp : Defines the entry point for the application.
// https://web.archive.org/web/20210803072351/http://www.obelisk.me.uk/6502

#include "6502Emulator.h"
using namespace std;

using Byte = uint8_t;  //8 Bits
using Word = uint16_t; //16 Bits
using u32 = unsigned int;

int main()
{
	Memory memory;
	CPU cpu;

	cpu.Reset(memory);

	//start - inline program
	memory[0xFFFC] = CPU::LDA_ZP;
	memory[0xFFFD] = 0x42;
	memory[0x0042] = 0x84;
	//end - inline program

	cpu.Execute(3, memory);

	return 0;
}
