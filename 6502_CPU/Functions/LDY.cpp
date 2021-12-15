#include "LDY.h"

void CPU::INS_LDY_IM_Function(unsigned int* Cycles)
{
	RegisterY = FetchByte(Cycles);
	SetZeroAndNegativeFlag(RegisterY);
}

void CPU::INS_LDY_ZP_Function(unsigned int* Cycles)
{
	Byte ZeroPageAdress = FetchByte(Cycles);
	RegisterY = ReadByteFromZeroPage(Cycles, ZeroPageAdress);
	SetZeroAndNegativeFlag(RegisterY);
}

void CPU::INS_LDY_ZPX_Function(unsigned int* Cycles)
{
	Byte Address = (Byte)AddrZeroPageX(Cycles);
	RegisterY = ReadByteFromZeroPage(Cycles, Address);
	SetZeroAndNegativeFlag(RegisterY);
}

void CPU::INS_LDY_ABS_Function(unsigned int* Cycles)
{
	Word AbsAddress = FetchWord(Cycles);
	RegisterY = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(RegisterY);
}

void CPU::INS_LDY_ABSX_Function(unsigned int* Cycles)
{
	Word AbsAddress = AddrAbsoluteX(Cycles);
	RegisterY = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(RegisterY);
}
