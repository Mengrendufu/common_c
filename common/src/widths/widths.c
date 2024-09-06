/* dependencies ------------------------------------------------------------*/
#include "stdio.h"
#include "widths.h"
/* dependencies ------------------------------------------------------------*/

/* count the types ---------------------------------------------------------*/
SystemDataTypeLengths system_data_type_lengths_get(void) {
    SystemDataTypeLengths lengths;

    /* Arrays to calculate the size difference between consecutive elements */
    unsigned char      uc_arr[2];
    unsigned short     ush_arr[2];
    unsigned int       ui_arr[2];
    unsigned long      ul_arr[2];
    unsigned long long ull_arr[2];
    void *             vp_arr[2];

    /* Assign the calculated sizes to the struct members */
    lengths.uc  = PTR_DISTANCE_BYTES(&uc_arr[0],  &uc_arr[1]);
    lengths.ush = PTR_DISTANCE_BYTES(&ush_arr[0], &ush_arr[1]);
    lengths.ui  = PTR_DISTANCE_BYTES(&ui_arr[0],  &ui_arr[1]);
    lengths.ul  = PTR_DISTANCE_BYTES(&ul_arr[0],  &ul_arr[1]);
    lengths.ull = PTR_DISTANCE_BYTES(&ull_arr[0], &ull_arr[1]);
    lengths.vp  = PTR_DISTANCE_BYTES(&vp_arr[0],  &vp_arr[1]);

    return lengths;
}
/* count the types ---------------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
void system_lengths_test(void) {
    SystemDataTypeLengths system_lengths = system_data_type_lengths_get();

    printf(
        "SYSTEM's sizeof(TYPE):\r\n"
        "TYPE -------------------- SIZE\r\n"
        "unsigned char         : %2dBYTE\r\n"
        "unsigned short        : %2dBYTE\r\n"
        "unsigned int          : %2dBYTE\r\n"
        "unsigned long int     : %2dBYTE\r\n"
        "unsigned long long int: %2dBYTE\r\n"
        "pointer               : %2dBYTE\r\n",

        system_lengths.uc,
        system_lengths.ush,
        system_lengths.ui,
        system_lengths.ul,
        system_lengths.ull,
        system_lengths.vp
    );

    return;
}
/* test area ---------------------------------------------------------------*/
