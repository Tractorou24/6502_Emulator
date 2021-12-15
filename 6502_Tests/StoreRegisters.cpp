#include "pch.h"
#include "CppUnitTest.h"
#include "../6502_CPU/CPU.h"
#include "../6502_CPU/CPU.cpp"
#include "../6502_CPU/CPU_Execute.cpp"
#include "../6502_CPU/Memory.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static void VerfifyUnmodifiedFlagsFromStoreRegister(const CPU cpu, const CPU CPUCopy)
{
	Assert::AreEqual(cpu.Flags.Carry, CPUCopy.Flags.Carry);
	Assert::AreEqual(cpu.Flags.InterruptDisable, CPUCopy.Flags.InterruptDisable);
	Assert::AreEqual(cpu.Flags.DisableMode, CPUCopy.Flags.DisableMode);
	Assert::AreEqual(cpu.Flags.BreakCommand, CPUCopy.Flags.BreakCommand);
	Assert::AreEqual(cpu.Flags.Overflow, CPUCopy.Flags.Overflow);
	Assert::AreEqual(cpu.Flags.Zero, CPUCopy.Flags.Zero);
	Assert::AreEqual(cpu.Flags.Negative, CPUCopy.Flags.Negative);
}

namespace Tests6502
{
	TEST_CLASS(StoreRegisterTests)
	{
	public:
		void TestStoreRegisterZeroPage(
			Byte OpcodeToTest,
			Byte CPU::*Register)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.*Register = 0x2F;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0x0080, 0x00);
			unsigned int EXPECTED_CYCLES = 3;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x0080), (Byte)0x2F);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestStoreRegisterAbsolute(
			Byte OpcodeToTest,
			Byte CPU::* Register)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.*Register = 0x2F;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x00);
			mem->SetData(0xFFFE, 0x80);
			mem->SetData(0x8000, 0x00);
			unsigned int EXPECTED_CYCLES = 4;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x8000),(Byte)0x2F);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestStoreRegisterZeroPageX(
			Byte OpcodeToTest,
			Byte CPU::* Register)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.*Register = 0x42;
			cpu.RegisterX = 0x0F;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0x008F, 0x00);
			unsigned int EXPECTED_CYCLES = 4;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x008F), (Byte)0x42);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestStoreRegisterZeroPageY(
			Byte OpcodeToTest,
			Byte CPU::* Register)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.*Register = 0x42;
			cpu.RegisterY = 0x0F;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0x008F, 0x00);
			unsigned int EXPECTED_CYCLES = 4;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x008F), (Byte)0x42);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(STAZeroPageCanStoreTheARegisterIntoMemory)
		{
			TestStoreRegisterZeroPage(INS_STA_ZP, &CPU::Accumulator);
		}

		TEST_METHOD(STXZeroPageCanStoreTheXRegisterIntoMemory)
		{
			TestStoreRegisterZeroPage(INS_STX_ZP, &CPU::RegisterX);
		}

		TEST_METHOD(STXZeroPageYCanStoreTheXRegisterIntoMemory)
		{
			TestStoreRegisterZeroPageY(INS_STX_ZPY, &CPU::RegisterX);
		}

		TEST_METHOD(STYZeroPageCanStoreTheYRegisterIntoMemory)
		{
			TestStoreRegisterZeroPage(INS_STY_ZP, &CPU::RegisterY);
		}

		TEST_METHOD(STAAbsoluteCanStoreTheARegisterIntoMemory)
		{
			TestStoreRegisterAbsolute(INS_STA_ABS, &CPU::Accumulator);
		}

		TEST_METHOD(STXAbsoluteCanStoreTheXRegisterIntoMemory)
		{
			TestStoreRegisterAbsolute(INS_STX_ABS, &CPU::RegisterX);
		}

		TEST_METHOD(STYAbsoluteCanStoreTheYRegisterIntoMemory)
		{
			TestStoreRegisterAbsolute(INS_STY_ABS, &CPU::RegisterY);
		}

		TEST_METHOD(STAZeroPageXCanStoreTheARegisterIntoMemory)
		{
			TestStoreRegisterZeroPageX(INS_STA_ZPX, &CPU::Accumulator);
		}

		TEST_METHOD(STYZeroPageXCanStoreTheYRegisterIntoMemory)
		{
			TestStoreRegisterZeroPageX(INS_STY_ZPX, &CPU::RegisterY);
		}

		TEST_METHOD(STAAbsoluteXCanStoreTheARegisterIntoMemory)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.Accumulator = 0x42;
			cpu.RegisterX = 0x0F;
			mem->SetData(0xFFFC, INS_STA_ABSX);
			mem->SetData(0xFFFD, 0x00);
			mem->SetData(0xFFFE, 0x80);
			unsigned int EXPECTED_CYCLES = 5;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x800F), (Byte)0x42);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(STAAbsoluteYCanStoreTheARegisterIntoMemory)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.Accumulator = 0x42;
			cpu.RegisterY = 0x0F;
			mem->SetData(0xFFFC, INS_STA_ABSY);
			mem->SetData(0xFFFD, 0x00);
			mem->SetData(0xFFFE, 0x80);
			unsigned int EXPECTED_CYCLES = 5;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x800F), (Byte)0x42);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(STAIndirectXCanStoreTheARegisterIntoMemory)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.Accumulator = 0x42;
			cpu.RegisterX = 0x0F;
			mem->SetData(0xFFFC, INS_STA_INDX);
			mem->SetData(0xFFFD, 0x20);
			mem->SetData(0x002F, 0x00);
			mem->SetData(0x0030, 0x80);
			mem->SetData(0x8000, 0x00);
			unsigned int EXPECTED_CYCLES = 6;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::AreEqual(mem->GetData(0x8000), (Byte)0x42);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(STAIndirectYCanStoreTheARegisterIntoMemory)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.Accumulator = 0x42;
			cpu.RegisterY = 0x0F;
			mem->SetData(0xFFFC, INS_STA_INDY);
			mem->SetData(0xFFFD, 0x20);
			mem->SetData(0x0020, 0x00);
			mem->SetData(0x0021, 0x80);
			mem->SetData(0x8000 + 0x0F, 0x00);
			unsigned int EXPECTED_CYCLES = 6;
			CPU CPUCopy = cpu;

			// when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			// then:
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::AreEqual(mem->GetData(0x800F), (Byte)0x42);
			VerfifyUnmodifiedFlagsFromStoreRegister(cpu, CPUCopy);
			delete mem;
		}
	};
}
