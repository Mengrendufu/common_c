#include <stdio.h>
#include "widths.h"

/* count the types ---------------------------------------------------------*/
SystemDataTypeLengths system_data_type_lengths_get(void) {
    SystemDataTypeLengths lengths;

    /* Arrays to calculate the size difference between consecutive elements */
    unsigned char          uc_arr[2];
    unsigned short int     ush_arr[2];
    unsigned int           ui_arr[2];
    unsigned long int      ul_arr[2];
    unsigned long long int ull_arr[2];
    void *                 vp_arr[2];
    float                  flt_arr[2];
    double                 fdb_arr[2];
    long double            fldb_arr[2];

    /* Assign the calculated sizes to the struct members */
    lengths.uc   = PTR_DISTANCE_BYTES(&uc_arr[0],   &uc_arr[1]);
    lengths.ush  = PTR_DISTANCE_BYTES(&ush_arr[0],  &ush_arr[1]);
    lengths.ui   = PTR_DISTANCE_BYTES(&ui_arr[0],   &ui_arr[1]);
    lengths.ul   = PTR_DISTANCE_BYTES(&ul_arr[0],   &ul_arr[1]);
    lengths.ull  = PTR_DISTANCE_BYTES(&ull_arr[0],  &ull_arr[1]);
    lengths.vp   = PTR_DISTANCE_BYTES(&vp_arr[0],   &vp_arr[1]);
    lengths.flt  = PTR_DISTANCE_BYTES(&flt_arr[0],  &flt_arr[1]);
    lengths.fdb  = PTR_DISTANCE_BYTES(&fdb_arr[0],  &fdb_arr[1]);
    lengths.fldb = PTR_DISTANCE_BYTES(&fldb_arr[0], &fldb_arr[1]);

    return lengths;
}
/* count the types ---------------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
void system_lengths_test(void) {
    SystemDataTypeLengths system_lengths = system_data_type_lengths_get();
    printf(
        "\r\n"
        "SYSTEM's sizeof(TYPE):\r\n"
        "-----------------------|----------------------\r\n"
        "        TYPE           |        SIZE\r\n"
        "-----------------------|----------------------\r\n"
        "unsigned char          | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "unsigned short int     | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "unsigned int           | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "unsigned long int      | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "unsigned long long int | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "pointer                | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "float                  | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "double                 | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "long double            | %2d BYTE ==> %3d bits\r\n"
        "-----------------------|----------------------\r\n"
        "\r\n",

        system_lengths.uc,   8 * system_lengths.uc,
        system_lengths.ush,  8 * system_lengths.ush,
        system_lengths.ui,   8 * system_lengths.ui,
        system_lengths.ul,   8 * system_lengths.ul,
        system_lengths.ull,  8 * system_lengths.ull,
        system_lengths.vp,   8 * system_lengths.vp,
        system_lengths.flt,  8 * system_lengths.flt,
        system_lengths.fdb,  8 * system_lengths.fdb,
        system_lengths.fldb, 8 * system_lengths.fldb);

    return;
}
/* test area ---------------------------------------------------------------*/
