//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "endian.h"

//============================================================================
bool isLittleEndian(void) {
    static uint16_t SNMTT_ROM u16 = 0x0001;
    return (*((uint8_t *)(&u16))) ? true : false;
}
