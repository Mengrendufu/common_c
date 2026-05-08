//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef SM_ENDIAN_H_
#define SM_ENDIAN_H_

//============================================================================
#include "endian_port.h"

// System endian judge. ======================================================
bool isLittleEndian(void);

// Convert. ==================================================================
#define SWAP_16(x) (                                                         \
    (((uint16_t)(x) & 0x00FFU) << 8) |                                       \
    (((uint16_t)(x) & 0xFF00U) >> 8)                                         \
)
#define SWAP_32(x) (                                                         \
    ((uint32_t)SWAP_16(((uint32_t)(x)) >> 16)) |                             \
    ((uint32_t)SWAP_16(((uint32_t)(x)) & 0xFFFFUL) << 16)                    \
)
#define SWAP_64(x) (                                                         \
    ((uint64_t)SWAP_32(((uint64_t)(x)) >> 32)) |                             \
    ((uint64_t)SWAP_32(((uint64_t)(x)) & 0xFFFFFFFFULL) << 32)               \
)

#endif // SM_ENDIAN_H_
