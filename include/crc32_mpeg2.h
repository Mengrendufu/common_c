//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC32_MPEG2_H_
#define CRC32_MPEG2_H_

//============================================================================
#include "crc_port.h"

//============================================================================
// name       : CRC32_MPEG2
// poly       : 0x04C11DB7
// reversePoly: 0xEDB88320
// init       : 0xFFFFFFFF
// refIn      : False
// refOut     : False
// xorOut     : 0x00000000
#define INIT_CRC32_MPEG2    0xFFFFFFFF
#define XOR_OUT_CRC32_MGEG2 0x00000000

uint32_t CRCIter_crc32_mpeg2(uint32_t prev,
                             uint8_t ch);

uint32_t crc32_mpeg2(uint8_t *arr,
                     uint16_t arrSize);

#endif // CRC32_MPEG2_H_
