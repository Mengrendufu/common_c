//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef P2UINT_H_
#define P2UINT_H_

//============================================================================
#include "p2uint_port.h"

//============================================================================
#define P2UINT(ptr_) ((P2UINT_Type)(ptr_))

//============================================================================
#define SM_CAST(type_, ptr_) ((type_ *)(ptr_))
#define VOID_CAST(ptr_) ((void *)(ptr_))

//============================================================================
#define SM_UNUSED(par) ((void)(par))

//============================================================================
#define SM_ARR_SIZE(arr_) (sizeof(arr_)/sizeof(arr_[0]))

//============================================================================
#ifndef offsetof
#define offsetof(type_, member_) \
    ((size_t)(&(((type_ *)0)->member_)))
#endif // ndef offsetof

#ifndef container_of
#define container_of(ptr_, type_, member_) \
    ((type_ *)(((char *)(ptr_ )) - offsetof(type_, member_)))
#endif // ndef container_of

#endif // P2UINT_H_
