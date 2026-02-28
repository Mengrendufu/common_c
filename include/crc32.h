//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC32_H_
#define CRC32_H_

//============================================================================
#include "crc_port.h"

//============================================================================
// name       : CRC32
// poly       : 0x04C11DB7
// reversePoly: 0xEDB88320
// init       : 0xFFFFFFFF
// refIn      : True
// refOut     : True
// xorOut     : 0xFFFFFFFF
#define INIT_CRC32   0xFFFFFFFF
#define XOROUT_CRC32 0xFFFFFFFF

uint32_t CRCIter_crc32(uint32_t prev,
                       uint8_t ch);

uint32_t crc32(uint8_t *arr,
               uint16_t arrSize);

#endif // CRC32_H_
