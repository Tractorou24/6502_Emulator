#include "Memory.h"

Memory::Memory()
{
	Initialise();
}

void Memory::Initialise()
{
	for (auto i = 0; i < MAX_MEM; i++)
		Data[i] = 0;
}

Byte Memory::GetData(unsigned int Address)
{
	return Data[Address];
}

void Memory::WriteWord(unsigned int Address, Word Value, unsigned int* Cycles)
{
	Data[Address] = Value & 0xFF;
	Data[Address + 1] = (Value >> 8);
	*Cycles -= 2;
}

void Memory::SetData(unsigned int Address, Byte newData)
{
	Data[Address] = newData;
}
