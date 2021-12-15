#ifndef LDY_H
#define LDY_H

#include "../CPU.h"

static constexpr Byte
	INS_LDY_IM = 0xA0,
	INS_LDY_ZP = 0xA4,
	INS_LDY_ZPX = 0xB4,
	INS_LDY_ABS = 0xAC,
	INS_LDY_ABSX = 0xBC;

#endif // !LDY_H
