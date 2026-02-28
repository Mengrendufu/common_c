//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC16_CCITT_H_
#define CRC16_CCITT_H_

//============================================================================
#include "crc_port.h"

//============================================================================
// name       : CRC16_CCITT
// poly       : 0x1021
// reversePoly: 0x8408
// init       : 0x0000
// refIn      : true
// refOut     : true
// xorOut     : 0x0000
#define INIT_CRC16_CCITT   0x0000
#define XOROUT_CRC16_CCITT 0x0000

uint16_t CRCIter_crc16_ccitt(uint16_t prev,
                             uint8_t ch);

uint16_t crc16_ccitt(uint8_t *arr,
                     uint16_t arrSize);

#endif // CRC16_CCITT_H_
