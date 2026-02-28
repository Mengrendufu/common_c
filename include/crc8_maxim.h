//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC8_MAXIM_H_
#define CRC8_MAXIM_H_

//============================================================================
#include "crc_port.h"

//============================================================================
// name       : CRC8_MAXIM
// poly       : 0x31
// reversePoly: 0x8C
// init       : 0x00
// refIn      : true
// refOut     : true
// xorOut     : 0x00
#define INIT_CRC8_MAXIM    0x00
#define XOROUT_CRC8_MAXIM  0x00

uint8_t CRCIter_crc8_maxim(uint8_t prev,
                           uint8_t ch);

uint8_t crc8_maxim(uint8_t *arr,
                   uint16_t arrSize);

#endif // CRC8_MAXIM_H_
