// https://web.archive.org/web/20210803072351/http://www.obelisk.me.uk/6502

#include "M6502Emulator.h"

void M6502::CPU::Execute(u32 Cycles, Memory& memory) {
    while (Cycles > 0) {
        Byte opcode = FetchByte(Cycles, memory);
        switch (opcode) {
            case LDA_IM: {
                //Loads a byte of memory into the accumalator
                //Z = 1 if A == 0
                //N = 1 if bit 7 of A is set
                Byte value = FetchByte(Cycles, memory);
                A = value;

                LDASetStatus();
            }
            case LDA_ZP: {
                //Loads a byte of memory into the accumalator
                //Z = 1 if A == 0
                //N = 1 if bit 7 of A is set
                Byte ZeroPageAddress = FetchByte(Cycles, memory);
                A = ReadByte(Cycles, memory, ZeroPageAddress);

                LDASetStatus();
            }
            case LDA_ZPX: {
                //Loads a byte of memory into the accumalator
                //Z = 1 if A == 0
                //N = 1 if bit 7 of A is set
                Byte ZeroPageAddress = FetchByte(Cycles, memory);
                ZeroPageAddress += X;
                Cycles--;
                A = ReadByte(Cycles, memory, ZeroPageAddress);

                LDASetStatus();
            }
            case JSR: {
                Word SubAddr = FetchWord(Cycles, memory);

                memory.WriteWord(Cycles, SP, PC - 1);
                PC = SubAddr;
                Cycles--;
            }
            default: {
                std::cerr << "Instruction not handled";
                break;
            }
        }
    }
}