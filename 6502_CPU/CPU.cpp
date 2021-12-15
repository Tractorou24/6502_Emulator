#include "CPU.h"

CPU::CPU(Memory* mem)
	: memory(mem)
{
	Reset(0xFFFC);
}

void CPU::Reset(Word ResetVector)
{
	ProgramCounter = ResetVector;
	StackPointer = 0xFF;
	Accumulator = RegisterX = RegisterY = 0;
	Flags.Carry = Flags.Zero = Flags.InterruptDisable = Flags.DisableMode = Flags.BreakCommand = Flags.Overflow = Flags.Negative = 0;

	memory->Initialise();
}

void CPU::PrintStatus()
{
	printf_s("ProgramCounter : 0x%x, StackPointer : 0x%x\n", ProgramCounter, StackPointer);
	printf_s("Accumulator : 0x%x, Register X : 0x%x, Register Y : 0x%x\n", Accumulator, RegisterX, RegisterY);
	printf_s("Flags -> Carry : 0x%x, Zero : 0x%x, InterruptDisable : 0x%x, DisableMod : 0x%x, BreakCommand : 0x%x, Overflow : 0x%x, Negative : 0x%x\n", 
		Flags.Carry, Flags.Zero, Flags.InterruptDisable, Flags.DisableMode, Flags.BreakCommand, Flags.Overflow, Flags.Negative);
}

Byte CPU::FetchByte(unsigned int* Cycles)
{
	Byte Data = memory->GetData(ProgramCounter);
	ProgramCounter++;
	*Cycles -= 1;
	return Data;
}

Byte CPU::ReadByte(unsigned int* Cycles, Word Address)
{
	Byte Data = memory->GetData(Address);
	*Cycles -= 1;
	return Data;
}

Word CPU::ReadWord(unsigned int* Cycles, Word Address)
{
	Byte LowByte = ReadByte(Cycles, Address);
	Byte HighByte = ReadByte(Cycles, Address + 1);
	return LowByte | (HighByte << 8);
}

Word CPU::FetchWord(unsigned int* Cycles)
{
	Word Data = memory->GetData(ProgramCounter);
	Data |= (memory->GetData(ProgramCounter + 1) << 8);
	ProgramCounter += 2;
	*Cycles -= 2;
	return Data;
}

Word CPU::AddrZeroPage(unsigned int* Cycles)
{
	Byte ZeroPageAdress = FetchByte(Cycles);
	return ZeroPageAdress;
}

Word CPU::AddrZeroPageX(unsigned int* Cycles)
{
	Byte ZeroPageAdress = FetchByte(Cycles);
	ZeroPageAdress += RegisterX;
	Cycles--;
	return ZeroPageAdress;
}

Word CPU::AddrZeroPageY(unsigned int* Cycles)
{
	Byte ZeroPageAdress = FetchByte(Cycles);
	ZeroPageAdress += RegisterY;
	Cycles--;
	return ZeroPageAdress;
}

Word CPU::AddrAbsolute(unsigned int* Cycles)
{
	return FetchWord(Cycles);
}

Word CPU::AddrAbsoluteX(unsigned int* Cycles) {
	Word AbsAddress = FetchWord(Cycles);
	Word AbsAddressX = AbsAddress + RegisterX;
	if (AbsAddressX - AbsAddress > 0xFF)
		*Cycles -= 1;

	return AbsAddressX;
}

Word CPU::AddrAbsoluteY(unsigned int* Cycles) {
	Word AbsAddress = FetchWord(Cycles);
	Word AbsAddressY = AbsAddress + RegisterY;
	if (AbsAddressY - AbsAddress > 0xFF)
		*Cycles -= 1;

	return AbsAddressY;
}

Word CPU::AddrIndX(unsigned int* Cycles) {
	Byte ZeroPageAddress = FetchByte(Cycles);
	ZeroPageAddress += RegisterX;
	*Cycles -= 1;
	return ReadWord(Cycles, ZeroPageAddress);
}

Word CPU::AddrIndY(unsigned int* Cycles) {
	Byte ZeroPageAddress = FetchByte(Cycles);
	Word EffectiveAddress = ReadWord(Cycles, ZeroPageAddress);
	return EffectiveAddress + RegisterY;
}

Word CPU::StackPointerToWord() const
{
	return 0x100 | StackPointer;
}

void CPU::WriteByte(Byte Value, unsigned int* Cycles, Word Address)
{
	memory->SetData(Address, Value);
	*Cycles -= 1;
}

void CPU::PushWordToStack(unsigned int* Cycles, Word Value)
{
	WriteByte(Value >> 8, Cycles, StackPointerToWord());
	StackPointer--;
	WriteByte(Value & 0xFF, Cycles, StackPointerToWord());
	StackPointer--;
}

Word CPU::PopWordFromStack(unsigned int* Cycles)
{
	Word ValueFromStack = ReadWord(Cycles, StackPointerToWord() + 1);
	StackPointer += 2;
	*Cycles -= 1;
	return ValueFromStack;
}

void CPU::SetZeroAndNegativeFlag(Byte Register)
{
	Flags.Zero = (Register == 0);
	Flags.Negative = (Register & 0b10000000) > 0;
}
