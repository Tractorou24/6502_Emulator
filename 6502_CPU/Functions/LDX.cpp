#include "LDX.h"

void CPU::INS_LDX_IM_Function(unsigned int* Cycles)
{
	RegisterX = FetchByte(Cycles);
	SetZeroAndNegativeFlag(RegisterX);
}

void CPU::INS_LDX_ZP_Function(unsigned int* Cycles)
{
	Byte ZeroPageAdress = FetchByte(Cycles);
	RegisterX = ReadByteFromZeroPage(Cycles, ZeroPageAdress);
	SetZeroAndNegativeFlag(RegisterX);
}

void CPU::INS_LDX_ZPY_Function(unsigned int* Cycles)
{
	Byte Address = (Byte)AddrZeroPageY(Cycles);
	RegisterX = ReadByteFromZeroPage(Cycles, Address);
	SetZeroAndNegativeFlag(RegisterX);
}

void CPU::INS_LDX_ABS_Function(unsigned int* Cycles)
{
	Word AbsAddress = FetchWord(Cycles);
	RegisterX = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(RegisterX);
}

void CPU::INS_LDX_ABSY_Function(unsigned int* Cycles)
{
	Word AbsAddress = AddrAbsoluteY(Cycles);
	RegisterX = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(RegisterX);
}
