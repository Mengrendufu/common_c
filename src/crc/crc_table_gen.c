/* dependencies ------------------------------------------------------------*/
#include <stdio.h>
#include "stdint.h"
#include "stdbool.h"
#include "stdlib.h"
#include "crc.h"
/* dependencies ------------------------------------------------------------*/

/* reverse the binary order of a byte and return ---------------------------*/
uint8_t get_reverse_byte(uint8_t byte) {
    uint8_t result;

    result = 0x00;
    for (uint8_t i = 0U; i < 8U; ++i) {
        result |= (((byte & (0x01 << i)) >> i) << (8U - i - 1U));
    }

    return result;
}
/* reverse the binary order of a byte and return ---------------------------*/

/* generate the crc-byte-table ---------------------------------------------*/
void crc_table_gen(
    uint8_t crc_width,
    uint8_t *poly,
    bool is_refin)
{
    /* get poly memory space -----------------------------------------------*/
    uint8_t *poly_  = (uint8_t *)malloc(crc_width / 8U);
    uint8_t *poly__ = (uint8_t *)malloc(crc_width / 8U);
    /* get poly memory space -----------------------------------------------*/

    /* get crc table's memory space ----------------------------------------*/
    uint16_t dat_;
    uint8_t *crc_ = (uint8_t *)malloc(crc_width / 8U);
    uint8_t *crc_table = (uint8_t *)malloc(256U * (crc_width / 8U));
    uint16_t table_idx = 0U;
    /* get crc table's memory space ----------------------------------------*/

    /* endian judge --------------------------------------------------------*/
    uint16_t tmp_ = 0xFF00;
    uint8_t *tmp__ = (uint8_t *)&tmp_;
    /* endian judge --------------------------------------------------------*/

    if (*tmp__) {
        /* big endian ------------------------------------------------------*/
        /* get poly input --------------------------------------------------*/
        for (uint8_t i = 0U; i < crc_width / 8U; ++i) {
            *(poly_ + i) = *(poly + i);
            *(poly__ + i) = *(poly + i);
        }
        /* get poly input --------------------------------------------------*/
        /* big endian ------------------------------------------------------*/
    }
    else {
        /* little endian ---------------------------------------------------*/
        /* get poly input --------------------------------------------------*/
        for (uint8_t i = 0; i < crc_width / 8U; ++i) {
            *(poly_ + i) =
                *(poly + crc_width / 8U - i - 1);

            *(poly__ + i) =
                *(poly + crc_width / 8U - i - 1);
        }
        /* get poly input --------------------------------------------------*/
        /* little endian ---------------------------------------------------*/
    }
    /* table generation ----------------------------------------------------*/
    if (is_refin) {
        /* get refin-poly --------------------------------------------------*/
        uint8_t tmp;
        for (uint8_t i = 0U; i < ((crc_width / 8U) + 1U) / 2U; ++i) {
            tmp = *(poly_ + i);
            *(poly_ + i) = *(poly_ + (crc_width / 8U) - i - 1U);
            *(poly_ + (crc_width / 8U) - i - 1U) = tmp;
        }
        /* get refin-poly --------------------------------------------------*/

        /* get reverse-refin-poly ------------------------------------------*/
        for (uint8_t i = 0U; i < crc_width / 8U; ++i) {
            *(poly_ + i) = get_reverse_byte(*(poly_ + i));
        }
        /* get reverse-refin-poly ------------------------------------------*/

        /* get table -------------------------------------------------------*/
        for (dat_ = 0x00; dat_ <= 0xFF; ++dat_) {
            /* init --------------------------------------------------------*/
            for (uint8_t i = 0U; i < crc_width / 8U; ++i) {
                crc_[i] = 0x00;
            }
            crc_[crc_width / 8U - 1U] = dat_;
            /* init --------------------------------------------------------*/

            /* calculate process -------------------------------------------*/
            for (uint8_t i = 0U; i < 8U; ++i) {
                if (crc_[crc_width / 8U - 1U] & 0x01) {
                    /* shift right -----------------------------------------*/
                    for (uint8_t j = 0U; j < crc_width / 8U - 1U; ++j) {
                        crc_[crc_width / 8U - j - 1U] >>= 1U;
                        if (crc_[crc_width / 8U - j - 1U - 1U] & 0x01) {
                            crc_[crc_width / 8U - j - 1U] |= 0x80;
                        }
                    }
                    crc_[0U] >>= 1U;
                    /* shift right -----------------------------------------*/

                    /* xor -------------------------------------------------*/
                    for (uint8_t k = 0U; k < crc_width / 8U; ++k) {
                        crc_[k] ^= poly_[k];
                    }
                    /* xor -------------------------------------------------*/
                }
                else {
                    /* shift right -----------------------------------------*/
                    for (uint8_t j = 0U; j < crc_width / 8U - 1U; ++j) {
                        crc_[crc_width / 8U - j - 1U] >>= 1U;
                        if (crc_[crc_width / 8U - j - 1U - 1U] & 0x01) {
                            crc_[crc_width / 8U - j - 1U] |= 0x80;
                        }
                    }
                    crc_[0U] >>= 1U;
                    /* shift right -----------------------------------------*/
                }
            }
            /* calculate process -------------------------------------------*/

            /* update table ------------------------------------------------*/
            for (uint8_t k = 0U; k < crc_width / 8U; ++k) {
                crc_table[table_idx] = crc_[k];
                ++table_idx;
            }
            /* update table ------------------------------------------------*/
        }
        /* get table -------------------------------------------------------*/
    }
    else {  /* is_refin */
        /* get table -------------------------------------------------------*/
        for (dat_ = 0x00; dat_ <= 0xFF; ++dat_) {
            /* init --------------------------------------------------------*/
            for (uint8_t i = 0U; i < crc_width / 8U; ++i) {
                crc_[i] = 0x00;
            }
            crc_[0U] = dat_;
            /* init --------------------------------------------------------*/

            /* calculate process -------------------------------------------*/
            for (uint8_t i = 0U; i < 8U; ++i) {
                if (crc_[0U] & 0x80) {
                    /* shift left ------------------------------------------*/
                    for (uint8_t j = 0U; j < crc_width / 8U - 1U; ++j) {
                        crc_[j] <<= 1U;
                        if (crc_[j + 1U] & 0x80) {
                            crc_[j] |= 0x01;
                        }
                    }
                    crc_[crc_width / 8U - 1U] <<= 1U;
                    /* shift left ------------------------------------------*/

                    /* xor -------------------------------------------------*/
                    for (uint8_t k = 0U; k < crc_width / 8U; ++k) {
                        crc_[k] ^= poly_[k];
                    }
                    /* xor -------------------------------------------------*/
                }
                else {
                    /* shift left ------------------------------------------*/
                    for (uint8_t j = 0U; j < crc_width / 8U - 1U; ++j) {
                        crc_[j] <<= 1U;
                        if (crc_[j + 1U] & 0x80) {
                            crc_[j] |= 0x01;
                        }
                    }
                    crc_[crc_width / 8U - 1U] <<= 1U;
                    /* shift left ------------------------------------------*/
                }
            }
            /* calculate process -------------------------------------------*/

            /* update table ------------------------------------------------*/
            for (uint8_t k = 0U; k < crc_width / 8U; ++k) {
                crc_table[table_idx] = crc_[k];
                ++table_idx;
            }
            /* update table ------------------------------------------------*/
        }
        /* get table -------------------------------------------------------*/
    }
    /* table generation ----------------------------------------------------*/

    /*! OUT: print table generated in console ------------------------------*/
    /* titles --------------------------------------------------------------*/
    printf("%-16s%-16s%-16s\r\n",
            "WIDTH", "POLY", "REFIN");

    printf("%-16d", crc_width);

    printf("0x");
    for (uint8_t i = 0U; i < crc_width / 8U; ++i) {
        printf("%02X", poly__[i]);
    }

    for (uint8_t i = 0U; i < 16U - crc_width / 4U - 2U; ++i) {
        printf(" ");
    }

    if (is_refin) {
        printf("%-16s", "TRUE");
    }
    else {
        printf("%-16s", "FALSE");
    }

    printf("\r\n");
    /* titles --------------------------------------------------------------*/

    /* tables --------------------------------------------------------------*/
    table_idx = 0U;
    for (uint16_t i = 0U; i <= 0xFF; ++i) {
        printf("0x");
        for (uint8_t j = 0U; j < crc_width / 8U; ++j) {
            printf("%02X", crc_table[table_idx]);
            ++table_idx;
        }
        if (i != 0xFF) {
            printf(", ");
        }
        if ((crc_width / 8U) <= 2U) {
            if (table_idx % (crc_width / 8U * 8U) == 0U) {
                printf("\r\n");
            }
        }
        else {
            if (table_idx % (crc_width / 8U * 4U) == 0U) {
                printf("\r\n");
            }
        }
    }
    /* tables --------------------------------------------------------------*/
    /*! OUT: print table generated in console ------------------------------*/

    /* memory free ---------------------------------------------------------*/
    /* free poly memory space ----------------------------------------------*/
    free(poly_);
    poly_ = NULL;

    free(poly__);
    poly__ = NULL;
    /* free poly memory space ----------------------------------------------*/

    /* free table memory space ---------------------------------------------*/
    free(crc_table);
    crc_table = NULL;
    /* free table memory space ---------------------------------------------*/

    /* free crc memory space -----------------------------------------------*/
    free(crc_);
    crc_ = NULL;
    /* free crc memory space -----------------------------------------------*/
    /* memory free ---------------------------------------------------------*/

    return;
}
/* generate the crc-byte-table ---------------------------------------------*/
