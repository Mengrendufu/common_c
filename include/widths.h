//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef WIDTH_H_
#define WIDTH_H_

//============================================================================
#define PTR_DISTANCE_BYTES(ptr1, ptr2) \
    ((unsigned char)((unsigned char *)(ptr2) - (unsigned char *)(ptr1)))

//============================================================================
typedef struct WidthInfo {
    unsigned char uc;   // sizeof(unsigned char).
    unsigned char ush;  // sizeof(unsigned short).
    unsigned char ui;   // sizeof(unsigned int).
    unsigned char ul;   // sizeof(unsigned long).
    unsigned char ull;  // sizeof(unsigned long long).
    unsigned char vp;   // sizeof(void*): pointer type.
    unsigned char flt;  // sizeof(float).
    unsigned char fdb;  // sizeof(double).
    unsigned char fldb; // sizeof(long double).
} WidthInfo;

WidthInfo Width_getTypeLength(void);

#endif // WIDTH_H_
