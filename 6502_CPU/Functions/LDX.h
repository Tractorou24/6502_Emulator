#ifndef LDX_H
#define LDX_H

#include "../CPU.h"

static constexpr Byte
	INS_LDX_IM = 0xA2,
	INS_LDX_ZP = 0xA6,
	INS_LDX_ZPY = 0xB6,
	INS_LDX_ABS = 0xAE,
	INS_LDX_ABSY = 0xBE;

#endif // !LDX_H
