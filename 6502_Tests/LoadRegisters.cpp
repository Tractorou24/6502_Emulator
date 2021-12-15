#include "pch.h"
#include "CppUnitTest.h"
#include "../6502_CPU/CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static void VerfifyUnmodifiedFlagsFromLoadRegister(const CPU cpu, const CPU CPUCopy)
{
	Assert::AreEqual(cpu.Flags.Carry, CPUCopy.Flags.Carry);
	Assert::AreEqual(cpu.Flags.InterruptDisable, CPUCopy.Flags.InterruptDisable);
	Assert::AreEqual(cpu.Flags.DisableMode, CPUCopy.Flags.DisableMode);
	Assert::AreEqual(cpu.Flags.BreakCommand, CPUCopy.Flags.BreakCommand);
	Assert::AreEqual(cpu.Flags.Overflow, CPUCopy.Flags.Overflow);
}

namespace Tests6502
{
	TEST_CLASS(LoadRegisterTests)
	{
	public:

		TEST_METHOD(TheCPUDoesNothingWhenWeExecuteZeroCycles)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			//given:
			unsigned int NUM_CYCLES = 0;

			//when:
			NUM_CYCLES = cpu.Execute(&NUM_CYCLES);

			//then:
			Assert::AreEqual(NUM_CYCLES, (unsigned int)0);
			delete mem;
		}

		void TestLoadRegisterImmediate(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD,  0x84);

			//when:
			CPU CPUCopy = cpu;
			unsigned int CYCLES = 2;
			CYCLES = cpu.Execute(&CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x84);
			Assert::AreEqual(CYCLES, (unsigned int)0);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsTrue(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAImmediateCanLoadAValueIntoTheARegister)
		{
			TestLoadRegisterImmediate(INS_LDA_IM, &CPU::Accumulator);
		}

		TEST_METHOD(LDXImmediateCanLoadAValueIntoTheXRegister)
		{
			TestLoadRegisterImmediate(INS_LDX_IM, &CPU::RegisterX);
		}

		TEST_METHOD(LDYImmediateCanLoadAValueIntoTheYRegister)
		{
			TestLoadRegisterImmediate(INS_LDY_IM, &CPU::RegisterY);
		}

		void TestLoadRegisterZeroPage(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);
			// given:
			
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x42);
			mem->SetData(0x0042, 0x37);

			//when:
			CPU CPUCopy = cpu;
			unsigned int CYCLES = 3;
			CYCLES = cpu.Execute(&CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual(CYCLES, (unsigned int)0);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAZeroPageCanLoadAValueIntoTheARegister)
		{
			TestLoadRegisterZeroPage(INS_LDA_ZP, &CPU::Accumulator);
		}

		TEST_METHOD(LDXZeroPageCanLoadAValueIntoTheXRegister)
		{
			TestLoadRegisterZeroPage(INS_LDX_ZP, &CPU::RegisterX);
		}

		TEST_METHOD(LDYZeroPageCanLoadAValueIntoTheYRegister)
		{
			TestLoadRegisterZeroPage(INS_LDY_ZP, &CPU::RegisterY);
		}

		TEST_METHOD(LDAImmediateCanAffectTheZeroFlag)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.Accumulator = 0x44;
			mem->SetData(0xFFFC, INS_LDA_IM);
			mem->SetData(0xFFFD, 0x0);
			CPU CPUCopy = cpu;

			//when:
			unsigned int CYCLES = 2;
			CYCLES = cpu.Execute(&CYCLES);

			//then:
			Assert::AreEqual(CYCLES, (unsigned int)0);
			Assert::IsTrue(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestLoadRegisterZeroPageX(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.RegisterX = 5;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x42);
			mem->SetData(0x0047, 0x37);
			CPU CPUCopy = cpu;

			//when:
			unsigned int CYCLES = 4;
			CYCLES = cpu.Execute(&CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual(CYCLES, (unsigned int)0);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestLoadRegisterZeroPageY(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);
			// given:
			
			cpu.RegisterY = 5;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x42);
			mem->SetData(0x0047, 0x37);
			CPU CPUCopy = cpu;

			//when:
			unsigned int CYCLES = 4;
			CYCLES = cpu.Execute(&CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual(CYCLES, (unsigned int)0);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAZeroPageXCanLoadAValueIntoTheARegister)
		{
			TestLoadRegisterZeroPageX(INS_LDA_ZPX, &CPU::Accumulator);
		}

		TEST_METHOD(LDXZeroPageYCanLoadAValueIntoTheXRegister)
		{
			TestLoadRegisterZeroPageY(INS_LDX_ZPY, &CPU::RegisterX);
		}

		TEST_METHOD(LDYZeroPageXCanLoadAValueIntoTheYRegister)
		{
			TestLoadRegisterZeroPageX(INS_LDY_ZPX, &CPU::RegisterY);
		}

		TEST_METHOD(LDAZeroPageXCanLoadAValueIntoTheARegisterWhenItWraps)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.RegisterX = 0xFF;
			mem->SetData(0xFFFC, INS_LDA_ZPX);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0x007F, 0x37);

			//when:
			CPU CPUCopy = cpu;
			unsigned int CYCLES = 4;
			CYCLES = cpu.Execute(&CYCLES);

			//then:
			Assert::AreEqual(cpu.Accumulator, (Byte)0x37);
			Assert::AreEqual(CYCLES, (unsigned int)0);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestLoadRegisterAbsolute(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.Flags.Zero = cpu.Flags.Negative = true;
			
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0xFFFE, 0x44);
			mem->SetData(0x4480, 0x37);
			unsigned int EXPECTED_CYCLES = 4;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual(EXPECTED_CYCLES, (unsigned int)0);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAAbsoluteCanLoadAValueIntoTheARegister)
		{
			TestLoadRegisterAbsolute(INS_LDA_ABS, &CPU::Accumulator);
		}

		TEST_METHOD(LDXAbsoluteCanLoadAValueIntoTheXRegister)
		{
			TestLoadRegisterAbsolute(INS_LDX_ABS, &CPU::RegisterX);
		}

		TEST_METHOD(LDYAbsoluteCanLoadAValueIntoTheYRegister)
		{
			TestLoadRegisterAbsolute(INS_LDY_ABS, &CPU::RegisterY);
		}

		void TestLoadRegisterAbsoluteX(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			cpu.Flags.Zero = cpu.Flags.Negative = true;
			
			cpu.RegisterX = 1;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0xFFFE, 0x44);
			mem->SetData(0x4481, 0x37);
			unsigned int EXPECTED_CYCLES = 4;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		void TestLoadRegisterAbsoluteY(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.Flags.Zero = cpu.Flags.Negative = true;
			cpu.RegisterY = 1;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0x80);
			mem->SetData(0xFFFE, 0x44);
			mem->SetData(0x4481, 0x37);
			unsigned int EXPECTED_CYCLES = 4;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAAbsoluteXCanLoadAValueIntoTheARegister)
		{
			TestLoadRegisterAbsoluteX(INS_LDA_ABSX, &CPU::Accumulator);
		}

		TEST_METHOD(LDXAbsoluteYCanLoadAValueIntoTheXRegister)
		{
			TestLoadRegisterAbsoluteY(INS_LDX_ABSY, &CPU::RegisterX);
		}

		TEST_METHOD(LDYAbsoluteXCanLoadAValueIntoTheYRegister)
		{
			TestLoadRegisterAbsoluteX(INS_LDY_ABSX, &CPU::RegisterY);
		}

		void TestLoadRegisterAbsoluteXWhenCrossingPage(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.RegisterX = 0x1;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0xFF);
			mem->SetData(0xFFFE, 0x44);	//0x44FF
			mem->SetData(0x4500, 0x37);	//0x44FF+0x1 crosses page boundary!
			unsigned int EXPECTED_CYCLES = 5;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAAbsoluteXCanLoadAValueIntoTheARegisterWhenItCrossesAPageBoundary)
		{
			TestLoadRegisterAbsoluteXWhenCrossingPage(INS_LDA_ABSX, &CPU::Accumulator);
		}

		TEST_METHOD(LDYAbsoluteXCanLoadAValueIntoTheYRegisterWhenItCrossesAPageBoundary)
		{
			TestLoadRegisterAbsoluteXWhenCrossingPage(INS_LDY_ABSX, &CPU::RegisterY);
		}

		TEST_METHOD(LDAAbsoluteYCanLoadAValueIntoTheARegister)
		{
			TestLoadRegisterAbsoluteY(INS_LDA_ABSY, &CPU::Accumulator);
		}

		void TestLoadRegisterAbsoluteYWhenCrossingPage(
			Byte OpcodeToTest,
			Byte CPU::* RegisterToTest)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.RegisterY = 0x1;
			mem->SetData(0xFFFC, OpcodeToTest);
			mem->SetData(0xFFFD, 0xFF);
			mem->SetData(0xFFFE, 0x44);	//0x44FF
			mem->SetData(0x4500, 0x37);	//0x44FF+0x1 crosses page boundary!
			unsigned int EXPECTED_CYCLES = 5;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.*RegisterToTest, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAAbsoluteYCanLoadAValueIntoTheARegisterWhenItCrossesAPageBoundary)
		{
			TestLoadRegisterAbsoluteYWhenCrossingPage(INS_LDA_ABSY, &CPU::Accumulator);
		}

		TEST_METHOD(LDXAbsoluteYCanLoadAValueIntoTheXRegisterWhenItCrossesAPageBoundary)
		{
			TestLoadRegisterAbsoluteYWhenCrossingPage(INS_LDX_ABSY, &CPU::RegisterX);
		}

		TEST_METHOD(LDAIndirectXCanLoadAValueIntoTheARegister)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.Flags.Zero = cpu.Flags.Negative = true;
			cpu.RegisterX = 0x04;
			mem->SetData(0xFFFC, INS_LDA_INDX);
			mem->SetData(0xFFFD, 0x02);
			mem->SetData(0x0006, 0x00);	//0x2 + 0x4
			mem->SetData(0x0007, 0x80);
			mem->SetData(0x8000, 0x37);
			unsigned int EXPECTED_CYCLES = 6;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.Accumulator, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAIndirectYCanLoadAValueIntoTheARegister)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.Flags.Zero = cpu.Flags.Negative = true;
			cpu.RegisterY = 0x04;
			mem->SetData(0xFFFC, INS_LDA_INDY);
			mem->SetData(0xFFFD, 0x02);
			mem->SetData(0x0002, 0x00);
			mem->SetData(0x0003, 0x80);
			mem->SetData(0x8004, 0x37);	//0x8000 + 0x4

			unsigned int EXPECTED_CYCLES = 5;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.Accumulator, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		}

		TEST_METHOD(LDAIndirectYCanLoadAValueIntoTheARegisterWhenItCrossesAPage)
		{
			Memory* mem = new Memory();
			CPU cpu(mem);
			cpu.Reset(0xFFFC);

			// given:
			
			cpu.RegisterY = 0x1;
			mem->SetData(0xFFFC, INS_LDA_INDY);
			mem->SetData(0xFFFD, 0x05);
			mem->SetData(0x0005, 0xFF);
			mem->SetData(0x0006, 0x80);
			mem->SetData(0x8100, 0x37);	//0x80FF + 0x1
			unsigned int EXPECTED_CYCLES = 6;
			CPU CPUCopy = cpu;

			//when:
			EXPECTED_CYCLES = cpu.Execute(&EXPECTED_CYCLES);

			//then:
			Assert::AreEqual(cpu.Accumulator, (Byte)0x37);
			Assert::AreEqual((unsigned int)0, EXPECTED_CYCLES);
			Assert::IsFalse(cpu.Flags.Zero);
			Assert::IsFalse(cpu.Flags.Negative);
			VerfifyUnmodifiedFlagsFromLoadRegister(cpu, CPUCopy);
			delete mem;
		};
	};
}
