#include "CPU.h"
#include "Memory.h"

int main(int argc, char* argv[]) {
	Memory* RAM = new Memory();
	CPU _6502(RAM);

	_6502.Reset(0xFFFC);

	RAM->SetData(0xFFFC, INS_JSR);
	RAM->SetData(0xFFFD, 0x42);
	RAM->SetData(0xFFFE, 0x42);
	RAM->SetData(0x4242, INS_LDA_IM);
	RAM->SetData(0x4243, 0x84);

	unsigned int Cycles = 8;
	_6502.Execute(&Cycles);
	_6502.PrintStatus();

	delete RAM;
	return 0;
}
