//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "widths.h"

//============================================================================
WidthInfo Width_getTypeLength(void) {
    WidthInfo widthInfo;

    unsigned char          uc_  [2];
    unsigned short int     ush_ [2];
    unsigned int           ui_  [2];
    unsigned long int      ul_  [2];
    unsigned long long int ull_ [2];
    void *                 vp_  [2];
    float                  flt_ [2];
    double                 fdb_ [2];
    long double            fldb_[2];

    widthInfo.uc   = PTR_DISTANCE_BYTES(&uc_  [0],   &uc_[1]);
    widthInfo.ush  = PTR_DISTANCE_BYTES(&ush_ [0],  &ush_[1]);
    widthInfo.ui   = PTR_DISTANCE_BYTES(&ui_  [0],   &ui_[1]);
    widthInfo.ul   = PTR_DISTANCE_BYTES(&ul_  [0],   &ul_[1]);
    widthInfo.ull  = PTR_DISTANCE_BYTES(&ull_ [0],  &ull_[1]);
    widthInfo.vp   = PTR_DISTANCE_BYTES(&vp_  [0],   &vp_[1]);
    widthInfo.flt  = PTR_DISTANCE_BYTES(&flt_ [0],  &flt_[1]);
    widthInfo.fdb  = PTR_DISTANCE_BYTES(&fdb_ [0],  &fdb_[1]);
    widthInfo.fldb = PTR_DISTANCE_BYTES(&fldb_[0], &fldb_[1]);

    return widthInfo;
}
