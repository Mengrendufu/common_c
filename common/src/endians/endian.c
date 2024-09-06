/* dependencies ------------------------------------------------------------*/
#include "stdint.h"
#include "endians.h"
/* dependencies ------------------------------------------------------------*/

/* judge little endian or big endian ---------------------------------------*/
uint8_t is_little_endian(void) {
    union Endian_Check {
        uint16_t ui;
        uint8_t c[2U];
    } endian_test;

    endian_test.ui = 0x0001;

    if (endian_test.c[0U]) {  /* low byte at low address */
        return 1U;
    }
    else {
        return 0U;
    }
}
/* judge little endian or big endian ---------------------------------------*/

/* endian content convert --------------------------------------------------*/
/* uint16_t ----------------------------------------------------------------*/
uint16_t endian_convert_16(uint16_t convert_src) {
    /* converted result ----------------------------------------------------*/
    uint16_t conterted = 0U;
    /* converted result ----------------------------------------------------*/

    /* convert -------------------------------------------------------------*/
    for (uint8_t i = 0U; i < 2U; ++i) {
        conterted += (convert_src << (16U - i * 8U - 8U))
                        & (0xFF00 >> i * 8U);
        convert_src >>= 8U;
    }
    /* convert -------------------------------------------------------------*/

    return conterted;
}
/* uint16_t ----------------------------------------------------------------*/

/* uint32_t ----------------------------------------------------------------*/
uint32_t endian_convert_32(uint32_t convert_src) {
    /* converted result ----------------------------------------------------*/
    uint32_t conterted = 0U;
    /* converted result ----------------------------------------------------*/

    /* convert -------------------------------------------------------------*/
    for (uint8_t i = 0U; i < 4U; ++i) {
        conterted += (convert_src << (32U - i * 8U - 8U))
                        & (0xFF000000 >> i * 8U);
        convert_src >>= 8U;
    }
    /* convert -------------------------------------------------------------*/

    return conterted;
}
/* uint32_t ----------------------------------------------------------------*/

/* uint64_t ----------------------------------------------------------------*/
uint64_t endian_convert_64(uint64_t convert_src) {
    /* converted result ----------------------------------------------------*/
    uint64_t conterted = 0U;
    /* converted result ----------------------------------------------------*/

    /* convert -------------------------------------------------------------*/
    for (uint8_t i = 0U; i < 8U; ++i) {
        conterted += (convert_src << (64U - i * 8U - 8U))
                        & (0xFF00000000000000 >> i * 8U);
        convert_src >>= 8U;
    }
    /* convert -------------------------------------------------------------*/

    return conterted;
}
/* uint64_t ----------------------------------------------------------------*/
/* endian content convert --------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
void endian_test(void) {
    /* endian judge --------------------------------------------------------*/
    if (is_little_endian()) {
        printf("The system is little-endian.\r\n");
    }
    else {
        printf("The system is big-endian.\r\n");
    }
    /* endian judge --------------------------------------------------------*/

    /* endian content convert ----------------------------------------------*/
    /* uint16_t ------------------------------------------------------------*/
    uint16_t src_16 = 0x0102;
    uint16_t converted_16 = endian_convert_16(src_16);
    printf(
        "0x%0p ==> 0x%0p\r\n",

        src_16, converted_16);
    /* uint16_t ------------------------------------------------------------*/

    /* uint32_t ------------------------------------------------------------*/
    uint32_t src_32 = 0x01020304;
    uint32_t converted_32 = endian_convert_32(src_32);
    printf(
        "0x%0p ==> 0x%0p\r\n",

        src_32, converted_32);
    /* uint32_t ------------------------------------------------------------*/

    /* uint64_t ------------------------------------------------------------*/
    uint64_t src_64 = 0x0102030405060708;
    uint64_t converted_64 = endian_convert_64(src_64);
    printf(
        "0x%0p ==> 0x%0p\r\n",

        src_64, converted_64);
    /* uint64_t ------------------------------------------------------------*/
    /* endian content convert ----------------------------------------------*/

    return;
}
/* test area ---------------------------------------------------------------*/
