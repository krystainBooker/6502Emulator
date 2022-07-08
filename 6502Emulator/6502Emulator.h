// 6502Emulator.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

struct Memory
{
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];

	void Initialise()
	{
		for (u32 i = 0; i < MAX_MEM; i++)
		{
			Data[i] = 0;
		}
	}

	// Read 1 byte
	Byte operator[](u32 Address) const
	{
		// Assert here Address is < MAX_MEM
		return Data[Address];
	}

	// Write 1 byte
	Byte& operator[](u32 Address)
	{
		// Assert here Address is < MAX_MEM
		return Data[Address];
	}

	// Write 2 bytes
	void WriteWord(u32& Cycles, u32 Address, Word value)
	{
		Data[Address] = value & 0xFF;
		Data[Address + 1] = (value >> 8);
		Cycles -= 2;
	}
};

struct CPU
{
	Word PC;	  // Program counter
	Byte SP;      // Stack pointer

	Byte A, X, Y; // Registers

	// Status flags
	Byte C : 1;  // Carry flag: The carry flag is set if the last operation caused an overflow from bit 7 of the result or an underflow from bit 0. This condition is set during arithmetic, comparison and during logical shifts. It can be explicitly set using the 'Set Carry Flag' (SEC) instruction and cleared with 'Clear Carry Flag' (CLC).
	Byte Z : 1;  // Zero flag: The zero flag is set if the result of the last operation as was zero.
	Byte I : 1;  // Interrupt Disable: The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' (SEI)instruction.While this flag is set the processor will not respond to interrupts from devices until it is cleared by a 'Clear Interrupt Disable' (CLI)instruction.
	Byte D : 1;  // Decimal Mode: While the decimal mode flag is set the processor will obey the rules of Binary Coded Decimal(BCD) arithmetic during additionand subtraction.The flag can be explicitly set using 'Set Decimal Flag' (SED) and cleared with 'Clear Decimal Flag' (CLD).
	Byte B : 1;  // Break Command: The break command bit is set when a BRK instruction has been executedand an interrupt has been generated to process it.
	Byte V : 1;  // Overflow Flag: The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's complement result (e.g. adding to positive numbers and ending up with a negative result: 64 + 64 => -128). It is determined by looking at the carry between bits 6 and 7 and between bit 7 and the carry flag.
	Byte N : 1;  // Negative Flag: The negative flag is set if the result of the last operation had bit 7 set to a one.

	void Reset(Memory& memory)
	{
		//C64 reset sequence 
		//https://www.c64-wiki.com/wiki/Reset_(Process)

		PC = 0xFFFC;
		SP = 0x0100;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;

		memory.Initialise();
	}

	Byte FetchByte(u32& Cycles, Memory& memory)
	{
		Byte data = memory[PC];
		PC++;

		Cycles--;
		return data;
	}

	Word FetchWord(u32& Cycles, Memory& memory)
	{
		// 6502 is little endian
		Word data = memory[PC];
		PC++;

		data |= (memory[PC] << 8);
		PC++;

		//to hanlde endianness, swap bytes here

		Cycles -= 2;
		return data;
	}

	Byte ReadByte(u32& Cycles, Memory& memory, Byte Address)
	{
		Byte data = memory[Address];

		Cycles--;
		return data;
	}

	// OP Codes
	static constexpr Byte
		LDA_IM = 0xA9,
		LDA_ZP = 0xA5,
		LDA_ZPX = 0xB5,
		JSR = 0x20;

	void LDASetStatus()
	{
		Z = (A == 0);
		N = (A & 0b10000000) > 0;
	}

	void Execute(u32 Cycles, Memory& memory)
	{
		while (Cycles > 0)
		{
			Byte opcode = FetchByte(Cycles, memory);
			switch (opcode)
			{
			case LDA_IM:
			{
				//Loads a byte of memory into the accumalator
				//Z = 1 if A == 0
				//N = 1 if bit 7 of A is set
				Byte value = FetchByte(Cycles, memory);
				A = value;

				LDASetStatus();
			}
			case LDA_ZP:
			{
				//Loads a byte of memory into the accumalator
				//Z = 1 if A == 0
				//N = 1 if bit 7 of A is set
				Byte ZeroPageAddress = FetchByte(Cycles, memory);
				A = ReadByte(Cycles, memory, ZeroPageAddress);

				LDASetStatus();
			}
			case LDA_ZPX:
			{
				//Loads a byte of memory into the accumalator
				//Z = 1 if A == 0
				//N = 1 if bit 7 of A is set
				Byte ZeroPageAddress = FetchByte(Cycles, memory);
				ZeroPageAddress += X;
				Cycles--;
				A = ReadByte(Cycles, memory, ZeroPageAddress);

				LDASetStatus();
			}
			case JSR:
			{
				Word SubAddr = FetchWord(Cycles, memory);

				memory.WriteWord(Cycles, SP, PC - 1);
				PC = SubAddr;
				Cycles--;
			}
			default:
			{
				cerr << "Instruction not handled";
				break;
			}
			}
		}
	}
};