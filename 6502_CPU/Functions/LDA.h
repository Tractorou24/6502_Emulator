#ifndef LDA_H
#define LDA_H

#include "../CPU.h"

static constexpr Byte
	INS_LDA_IM = 0xA9,
	INS_LDA_ZP = 0xA5,
	INS_LDA_ZPX = 0xB5,
	INS_LDA_ABS = 0xAD,
	INS_LDA_ABSX = 0xBD,
	INS_LDA_ABSY = 0xB9,
	INS_LDA_INDX = 0xA1,
	INS_LDA_INDY = 0xB1;

#endif // !LDA_H