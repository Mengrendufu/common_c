//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "crc_table_gen.h"

//============================================================================
static uint8_t CRC_byteReverse(uint8_t byte) {
    uint8_t result;
    result = 0x00;
    for (uint8_t i = 0U; i < 8U; ++i) {
        result |= (((byte & (0x01 << i)) >> i) << (8U - i - 1U));
    }
    return result;
}

//............................................................................
void CRC_tableGen(uint8_t width,
                  uint8_t *poly,
                  bool isRefin)
{
    // Memory for poly...
    uint8_t *poly_  = (uint8_t *)malloc(width / 8U);
    uint8_t *poly__ = (uint8_t *)malloc(width / 8U);

    // Memory allocation...
    uint16_t dat_;
    uint8_t *crcIter = (uint8_t *)malloc(width / 8U);
    uint8_t *crcTable = (uint8_t *)malloc(256U * (width / 8U));
    uint16_t tblIdx = 0U;

    // System endian...
    uint16_t tmp_ = 0xFF00;
    uint8_t *tmp__ = (uint8_t *)&tmp_;
    if (*tmp__) {
        // Big-endian...
        for (uint8_t i = 0U; i < width / 8U; ++i) {
            *(poly_ + i)  = *(poly + i);
            *(poly__ + i) = *(poly + i);
        }
    } else {
        // Little endian...
        for (uint8_t i = 0; i < width / 8U; ++i) {
            *(poly_ + i)  = *(poly + width / 8U - i - 1);
            *(poly__ + i) = *(poly + width / 8U - i - 1);
        }
    }

    if (isRefin) { // Incoming reverse...
        // Get refin-poly...
        uint8_t tmp;
        for (uint8_t i = 0U; i < ((width / 8U) + 1U) / 2U; ++i) {
            tmp = *(poly_ + i);
            *(poly_ + i) = *(poly_ + (width / 8U) - i - 1U);
            *(poly_ + (width / 8U) - i - 1U) = tmp;
        }

        // Reverse...
        for (uint8_t i = 0U; i < width / 8U; ++i) {
            *(poly_ + i) = CRC_byteReverse(*(poly_ + i));
        }

        // Update CRC table...
        for (dat_ = 0x00; dat_ <= 0xFF; ++dat_) {
            // Init...
            for (uint8_t i = 0U; i < width / 8U; ++i) {
                crcIter[i] = 0x00;
            }
            crcIter[width / 8U - 1U] = dat_;

            // Generating iter crc...
            for (uint8_t i = 0U; i < 8U; ++i) {
                if (crcIter[width / 8U - 1U] & 0x01) {
                    // Shifting right...
                    for (uint8_t j = 0U; j < width / 8U - 1U; ++j) {
                        crcIter[width / 8U - j - 1U] >>= 1U;
                        if (crcIter[width / 8U - j - 1U - 1U] & 0x01) {
                            crcIter[width / 8U - j - 1U] |= 0x80;
                        }
                    }
                    crcIter[0U] >>= 1U;

                    // XOR...
                    for (uint8_t k = 0U; k < width / 8U; ++k) {
                        crcIter[k] ^= poly_[k];
                    }
                } else {
                    // Shifting right...
                    for (uint8_t j = 0U; j < width / 8U - 1U; ++j) {
                        crcIter[width / 8U - j - 1U] >>= 1U;
                        if (crcIter[width / 8U - j - 1U - 1U] & 0x01) {
                            crcIter[width / 8U - j - 1U] |= 0x80;
                        }
                    }
                    crcIter[0U] >>= 1U;
                }
            }

            // CRC table update...
            for (uint8_t k = 0U; k < width / 8U; ++k) {
                crcTable[tblIdx++] = crcIter[k];
            }
        }
    } else { // Original poly...
        for (dat_ = 0x00; dat_ <= 0xFF; ++dat_) {
            // Init...
            for (uint8_t i = 0U; i < width / 8U; ++i) {
                crcIter[i] = 0x00;
            }
            crcIter[0U] = dat_;

            // Generating iter crc...
            for (uint8_t i = 0U; i < 8U; ++i) {
                if (crcIter[0U] & 0x80) {
                    // Shifting left...
                    for (uint8_t j = 0U; j < width / 8U - 1U; ++j) {
                        crcIter[j] <<= 1U;
                        if (crcIter[j + 1U] & 0x80) {
                            crcIter[j] |= 0x01;
                        }
                    }
                    crcIter[width / 8U - 1U] <<= 1U;

                    // XOR...
                    for (uint8_t k = 0U; k < width / 8U; ++k) {
                        crcIter[k] ^= poly_[k];
                    }
                } else {
                    // Shifting left...
                    for (uint8_t j = 0U; j < width / 8U - 1U; ++j) {
                        crcIter[j] <<= 1U;
                        if (crcIter[j + 1U] & 0x80) {
                            crcIter[j] |= 0x01;
                        }
                    }
                    crcIter[width / 8U - 1U] <<= 1U;
                }
            }

            // CRC table update...
            for (uint8_t k = 0U; k < width / 8U; ++k) {
                crcTable[tblIdx] = crcIter[k];
                ++tblIdx;
            }
        }
    }

    // Generating output. ====================================================
    // Titles...
    printf("%-16s%-16s%-16s\r\n", "WIDTH", "POLY", "REFIN");
    printf("%-16d", width);
    printf("0x");
    for (uint8_t i = 0U; i < width / 8U; ++i) {
        printf("%02X", poly__[i]);
    }
    for (uint8_t i = 0U; i < 16U - width / 4U - 2U; ++i) {
        printf(" ");
    }
    if (isRefin) {
        printf("%-16s", "TRUE");
    }
    else {
        printf("%-16s", "FALSE");
    }
    printf("\r\n");

    // Tables...
    tblIdx = 0U;
    for (uint16_t i = 0U; i <= 0xFF; ++i) {
        printf("0x");
        for (uint8_t j = 0U; j < width / 8U; ++j) {
            printf("%02X", crcTable[tblIdx]);
            ++tblIdx;
        }

        if (i != 0xFF) {
            printf(", ");
        }

        if ((width / 8U) <= 2U) {
            if (tblIdx % (width / 8U * 8U) == 0U) {
                printf("\r\n");
            }
        } else {
            if (tblIdx % (width / 8U * 4U) == 0U) {
                printf("\r\n");
            }
        }
    }

    // GC... =================================================================
    free(poly_);
    free(poly__);
    free(crcTable);
    free(crcIter);
}
