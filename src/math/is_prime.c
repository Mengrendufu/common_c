//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include <is_prime.h>

//============================================================================
bool isPrime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if ((n & 1) == 0 || n % 3 == 0) return false;
    uint64_t i = 5;
    uint64_t step = 2;
    while (i * i <= n) {
        if (n % i == 0) return false;
        i += step;
        step = 6 - step; // 交替步长 2 和 4
    }
    return true;
}
