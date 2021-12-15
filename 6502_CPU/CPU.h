#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include "Memory.h"
#include "CPU_Execute.h"

struct CPUFlags
{
	Byte Carry : 1;
	Byte Zero : 1;
	Byte InterruptDisable : 1;
	Byte DisableMode : 1;
	Byte BreakCommand : 1;
	Byte Overflow : 1;
	Byte Negative : 1;
};

class CPU
{
public:
	CPU(Memory*);
	void Reset(Word);
	int Execute(unsigned int*);
	void PrintStatus();

	/***  A mettre en private pour la version finale (Ici pour les tests)  ***/
	Word ProgramCounter; // Program counter
	Byte StackPointer; // Stack pointer
	Byte Accumulator, RegisterX, RegisterY; // Registers
	Byte ProcessorStatus;
	CPUFlags Flags; // Flags

private:
	Byte FetchByte(unsigned int*);
	Byte ReadByte(unsigned int*, Word);
	Word ReadWord(unsigned int*, Word);
	Word FetchWord(unsigned int*);
	Word AddrZeroPage(unsigned int*);
	Word AddrZeroPageX(unsigned int*);
	Word AddrZeroPageY(unsigned int*);
	Word AddrAbsolute(unsigned int*);
	Word AddrAbsoluteX(unsigned int*);
	Word AddrAbsoluteY(unsigned int*);
	Word AddrIndX(unsigned int*);
	Word AddrIndY(unsigned int*);
	Word StackPointerToWord() const;
	Word PopWordFromStack(unsigned int*);
	void WriteByte(Byte, unsigned int*, Word);
	void PushWordToStack(unsigned int*, Word);
	void SetZeroAndNegativeFlag(Byte);

private:

	/***  Mettre les variables publiques indiquées ici :  ***/
	Memory* memory;
};

#endif