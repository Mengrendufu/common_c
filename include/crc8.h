//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC8_H_
#define CRC8_H_

//============================================================================
#include "crc_port.h"

//============================================================================
// poly       : 0x07
// reversePoly: 0xE0
// init       : 0x00
// refIn      : false
// refOut     : false
// xorOut     : 0x00
#define INIT_CRC8   0x00
#define XOROUT_CRC8 0x00

uint8_t CRCIter_crc8(uint8_t prev,
                     uint8_t ch);

uint8_t crc8(uint8_t *arr,
             uint16_t arrSize);

#endif // CRC8_H_
