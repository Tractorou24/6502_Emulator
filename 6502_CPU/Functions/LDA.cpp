#include "LDA.h"

void CPU::INS_LDA_IM_Function(unsigned int* Cycles)
{
	Accumulator = FetchByte(Cycles);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_ZP_Function(unsigned int* Cycles)
{
	Word Address = AddrZeroPage(Cycles);
	Accumulator = ReadByteFromZeroPage(Cycles, (Byte)Address);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_ZPX_Function(unsigned int* Cycles)
{
	Byte Address = (Byte)AddrZeroPageX(Cycles);
	Accumulator = ReadByteFromZeroPage(Cycles, (Byte)Address);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_ABS_Function(unsigned int* Cycles)
{
	Word AbsAddress = FetchWord(Cycles);
	Accumulator = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_ABSX_Function(unsigned int* Cycles)
{
	Word AbsAddress = AddrAbsoluteX(Cycles);
	Accumulator = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_ABSY_Function(unsigned int* Cycles)
{
	Word AbsAddress = AddrAbsoluteY(Cycles);
	Accumulator = ReadByte(Cycles, (Byte)AbsAddress);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_INDX_Function(unsigned int* Cycles)
{
	Word EffectiveAddress = AddrIndX(Cycles);
	Accumulator = ReadByte(Cycles, (Byte)EffectiveAddress);
	SetZeroAndNegativeFlag(Accumulator);
}

void CPU::INS_LDA_INDY_Function(unsigned int* Cycles)
{
	Word EffectiveAddressY = AddrIndY(Cycles);
	Accumulator = ReadByte(Cycles, (Byte)EffectiveAddressY);
	SetZeroAndNegativeFlag(Accumulator);
}
