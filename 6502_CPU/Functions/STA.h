#ifndef STA_H
#define STA_H

#include "../CPU.h"

static constexpr Byte
	INS_STA_ZP = 0x85,
	INS_STA_ZPX = 0x95,
	INS_STA_ABS = 0x8D,
	INS_STA_ABSX = 0x9D,
	INS_STA_ABSY = 0x99,
	INS_STA_INDX = 0x81,
	INS_STA_INDY = 0x91;

#endif // !STA_H
