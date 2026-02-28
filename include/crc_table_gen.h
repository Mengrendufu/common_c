//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef CRC_TABLE_GEN_H_
#define CRC_TABLE_GEN_H_

//============================================================================
#include "crc_port.h"

//============================================================================
//! @public Generate the CRC table via a specific POLY.
//! @param[in] width The bit width of CRC_x algorithm.
//! @param[in] poly Pointing to the poly, endian process inside.
//! @param[in] isRefin Is the refin option true?
void CRC_tableGen(uint8_t width,
                  uint8_t *poly,
                  bool isRefin);

#endif // CRC_TABLE_GEN_H_
