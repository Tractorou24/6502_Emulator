#ifndef MEMORY_H
#define MEMORY_H

using Byte = unsigned char;
using Word = unsigned short;

class Memory
{
public:
	Memory();
	void Initialise();
	void SetData(unsigned int, Byte);
	Byte GetData(unsigned int);
	void WriteWord(unsigned int, Word, unsigned int*);

private:
	static constexpr unsigned int MAX_MEM = 1204 * 64;
	Byte Data[MAX_MEM];
};

#endif