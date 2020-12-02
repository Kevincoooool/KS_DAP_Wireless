#ifndef __HEX2BIN_H
#define __HEX2BIN_H

#include "ff.h"
#include "string.h"
#include "oled.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef struct {
	uint8_t len;
	uint8_t	type;
	uint16_t addr;
	uint8_t data[512];
} BinFarmat;

char HexFormatUncode(unsigned char *File);

#endif /*_MAIN_H_*/


