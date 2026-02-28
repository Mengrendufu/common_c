//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC16_MAXIM_H_
#define CRC16_MAXIM_H_

//============================================================================
#include "crc_port.h"

//============================================================================
// name       : CRC16_MAXIM
// poly       : 0x8005
// reversePoly: 0xA001
// init       : 0x0000
// refIn      : true
// refOut     : true
// xorOut     : 0xFFFF
#define INIT_CRC16_MAXIM   0x0000
#define XOROUT_CRC16_MAXIM 0xFFFF

uint16_t CRCIter_crc16_maxim(uint16_t prev,
                             uint8_t ch);

uint16_t crc16_maxim(uint8_t *arr,
                     uint16_t arrSize);

#endif // CRC16_MAXIM_H_
