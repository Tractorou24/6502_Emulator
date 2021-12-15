#include "CPU_Execute.h"

int CPU::Execute(unsigned int* Cycles)
{
	while (*Cycles > 0) {
		Byte Instruction = FetchByte(Cycles);
		switch (Instruction)
		{
			/* -------------------------------------- LDA -------------------------------------- */
		case INS_LDA_IM: {
			Accumulator = FetchByte(Cycles);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_ZP: {
			Byte Address = (Byte)AddrZeroPage(Cycles);
			Accumulator = ReadByte(Cycles, Address);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_ZPX: {
			Byte Address = (Byte)AddrZeroPageX(Cycles);
			Accumulator = ReadByte(Cycles, Address);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_ABS: {
			Word Address = AddrAbsolute(Cycles);
			Accumulator = ReadByte(Cycles, Address);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_ABSX: {
			Word Address = AddrAbsoluteX(Cycles);
			Accumulator = ReadByte(Cycles, Address);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_ABSY: {
			Word AbsAddress = AddrAbsoluteY(Cycles);
			Accumulator = ReadByte(Cycles, AbsAddress);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_INDX: {
			Word EffectiveAddress = AddrIndX(Cycles);
			Accumulator = ReadByte(Cycles, EffectiveAddress);
			SetZeroAndNegativeFlag(Accumulator);
		} break;
		case INS_LDA_INDY: {
			Word EffectiveAddressY = AddrIndY(Cycles);
			Accumulator = ReadByte(Cycles, EffectiveAddressY);
			SetZeroAndNegativeFlag(Accumulator);
		} break;

			/* -------------------------------------- LDX -------------------------------------- */
		case INS_LDX_IM: {
			RegisterX = FetchByte(Cycles);
			SetZeroAndNegativeFlag(RegisterX);
		} break;
		case INS_LDX_ZP: {
			Byte ZeroPageAdress = FetchByte(Cycles);
			RegisterX = ReadByte(Cycles, ZeroPageAdress);
			SetZeroAndNegativeFlag(RegisterX);
		} break;
		case INS_LDX_ZPY: {
			Byte Address = (Byte)AddrZeroPageY(Cycles);
			RegisterX = ReadByte(Cycles, Address);
			SetZeroAndNegativeFlag(RegisterX);
		} break;
		case INS_LDX_ABS: {
			Word AbsAddress = AddrAbsolute(Cycles);
			RegisterX = ReadByte(Cycles, AbsAddress);
			SetZeroAndNegativeFlag(RegisterX);
		} break;
		case INS_LDX_ABSY: {
			Word AbsAddress = AddrAbsoluteY(Cycles);
			RegisterX = ReadByte(Cycles, AbsAddress);
			SetZeroAndNegativeFlag(RegisterX);
		} break;

			/* -------------------------------------- LDY -------------------------------------- */
		case INS_LDY_IM: {
			RegisterY = FetchByte(Cycles);
			SetZeroAndNegativeFlag(RegisterY);
		} break;
		case INS_LDY_ZP: {
			Byte ZeroPageAdress = FetchByte(Cycles);
			RegisterY = ReadByte(Cycles, ZeroPageAdress);
			SetZeroAndNegativeFlag(RegisterY);
		} break;
		case INS_LDY_ZPX: {
			Byte Address = (Byte)AddrZeroPageX(Cycles);
			RegisterY = ReadByte(Cycles, Address);
			SetZeroAndNegativeFlag(RegisterY);
		} break;
		case INS_LDY_ABS: {
			Word AbsAddress = AddrAbsolute(Cycles);
			RegisterY = ReadByte(Cycles, AbsAddress);
			SetZeroAndNegativeFlag(RegisterY);
		} break;
		case INS_LDY_ABSX: {
			Word AbsAddress = AddrAbsoluteX(Cycles);
			RegisterY = ReadByte(Cycles, AbsAddress);
			SetZeroAndNegativeFlag(RegisterY);
		} break;

			/* -------------------------------------- STA -------------------------------------- */
		case INS_STA_ZP: {
			Byte Address = (Byte)AddrZeroPage(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;
		case INS_STA_ZPX: {
			Byte Address = (Byte)AddrZeroPageX(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;
		case INS_STA_ABS: {
			Word Address = AddrAbsolute(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;
		case INS_STA_ABSX: {
			Word Address = AddrAbsoluteX(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;
		case INS_STA_ABSY: {
			Word Address = AddrAbsoluteY(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;
		case INS_STA_INDX: {
			Word Address = AddrIndX(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;
		case INS_STA_INDY: {
			Word Address = AddrIndY(Cycles);
			WriteByte(Accumulator, Cycles, Address);
		} break;

			/* -------------------------------------- STX -------------------------------------- */
		case INS_STX_ZP: {
			Byte Address = (Byte)AddrZeroPage(Cycles);
			WriteByte(RegisterX, Cycles, Address);
		} break;
		case INS_STX_ZPY: {
			Byte Address = (Byte)AddrZeroPageY(Cycles);
			WriteByte(RegisterX, Cycles, Address);
		} break;
		case INS_STX_ABS: {
			Word Address = AddrAbsolute(Cycles);
			WriteByte(RegisterX, Cycles, Address);
		} break;

			/* -------------------------------------- STY -------------------------------------- */
		case INS_STY_ZP: {
			Byte Address = (Byte)AddrZeroPage(Cycles);
			WriteByte(RegisterY, Cycles, Address);
		} break;
		case INS_STY_ZPX: {
			Byte Address = (Byte)AddrZeroPageX(Cycles);
			WriteByte(RegisterY, Cycles, Address);
		} break;
		case INS_STY_ABS: {
			Word Address = AddrAbsolute(Cycles);
			WriteByte(RegisterY, Cycles, Address);
		} break;

			/* -------------------------------------- MISC -------------------------------------- */
		case INS_JSR: {
			Word SubAddr = FetchWord(Cycles);
			PushWordToStack(Cycles, ProgramCounter - 1);
			ProgramCounter = SubAddr;
			*Cycles -= 1;
		} break;
		case INS_RTS: {
			Word ReturnAddress = PopWordFromStack(Cycles);
			ProgramCounter = ReturnAddress + 1;
			*Cycles -= 2;
		} break;
		case INS_JMP_ABS: {
			Word Address = AddrAbsolute(Cycles);
			ProgramCounter = Address;
		} break;
		case INS_JMP_IND: {
			Word Address = AddrAbsolute(Cycles);
			Address = ReadWord(Cycles, Address);
			ProgramCounter = Address;
		} break;
		default: {
			printf_s("Instruction %d not handled !\n", Instruction);
		} break;
		}
	}
	return *Cycles;
}
