#include "pch.h"
#include "CppUnitTest.h"
#include "../6502_CPU/CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests6502
{
	TEST_CLASS(JumpAndCallsTests)
	{
	public:
		TEST_METHOD(CanJumpToASubroutineAndJumpBackAgain)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFF00);

			// given:
			mem->SetData(0xFF00, INS_JSR);
			mem->SetData(0xFF01, 0x00);
			mem->SetData(0xFF02, 0x80);
			mem->SetData(0x8000, INS_RTS);
			mem->SetData(0xFF03, INS_LDA_IM);
			mem->SetData(0xFF04, 0x42);
			unsigned int EXPECTED_CYCLES = 6 + 6 + 2;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::AreEqual(cpu.Accumulator, (Byte)0x42);
			auto a = (Byte)cpu.StackPointer;
			auto b = (Byte)CPUCopy.StackPointer;
			Assert::AreEqual((Byte)cpu.StackPointer, (Byte)CPUCopy.StackPointer);
			delete mem;
		}

		TEST_METHOD(JSRDoesNotAffectTheProcessorStatus)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFF00);

			// given:
			cpu.Reset(0xFF00);
			mem->SetData(0xFF00, INS_JSR);
			mem->SetData(0xFF01, 0x00);
			mem->SetData(0xFF02, 0x80);
			unsigned int EXPECTED_CYCLES = 6;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::AreEqual(cpu.ProcessorStatus, CPUCopy.ProcessorStatus);
			Assert::AreNotEqual((Byte)cpu.StackPointer, (Byte)CPUCopy.StackPointer);
			Assert::AreEqual((Byte)cpu.ProgramCounter, (Byte)0x8000);
			delete mem;
		}

		TEST_METHOD(RTSDoesNotAffectTheProcessorStatus)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFF00);

			// given:
			mem->SetData(0xFF00, INS_JSR);
			mem->SetData(0xFF01, 0x00);
			mem->SetData(0xFF02, 0x80);
			mem->SetData(0x8000, INS_RTS);
			unsigned int EXPECTED_CYCLES = 6 + 6;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::AreEqual(cpu.ProcessorStatus, CPUCopy.ProcessorStatus);
			Assert::AreEqual((Byte)cpu.ProgramCounter, (Byte)0xFF03);
			delete mem;
		}

		TEST_METHOD(JumpAbsoluteCanJumpToAnNewLocationInTheProgram)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFF00);

			// given:
			mem->SetData(0xFF00, INS_JMP_ABS);
			mem->SetData(0xFF01, 0x00);
			mem->SetData(0xFF02, 0x80);
			unsigned int EXPECTED_CYCLES = 3;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::AreEqual(cpu.ProcessorStatus, CPUCopy.ProcessorStatus);
			Assert::AreEqual((Byte)cpu.StackPointer, (Byte)CPUCopy.StackPointer);
			Assert::AreEqual((Byte)cpu.ProgramCounter, (Byte)0x8000);
			delete mem;
		}

		TEST_METHOD(JumpIndirectCanJumpToAnNewLocationInTheProgram)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFF00);

			// given:
			mem->SetData(0xFF00, INS_JMP_IND);
			mem->SetData(0xFF01, 0x00);
			mem->SetData(0xFF02, 0x80);
			mem->SetData(0x8000, 0x00);
			mem->SetData(0x8001, 0x90);
			unsigned int EXPECTED_CYCLES = 5;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::AreEqual(cpu.ProcessorStatus, CPUCopy.ProcessorStatus);
			Assert::AreEqual((Byte)cpu.StackPointer, (Byte)CPUCopy.StackPointer);
			Assert::AreEqual((Byte)cpu.ProgramCounter, (Byte)0x9000);
			delete mem;
		}
	};
}
