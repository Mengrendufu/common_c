#ifndef widths_h_
#define widths_h_

/* helper macro used inside ------------------------------------------------*/
#define PTR_DISTANCE_BYTES(ptr1, ptr2) \
    ((unsigned char)((unsigned char *)(ptr2) - (unsigned char *)(ptr1)))
/* helper macro used inside ------------------------------------------------*/

/* struct to store lengths of various system data types --------------------*/
typedef struct SystemDataTypeLengths {
    unsigned char  uc;          /* sizeof(unsigned char) */
    unsigned char  ush;         /* sizeof(unsigned short) */
    unsigned char  ui;          /* sizeof(unsigned int) */
    unsigned char  ul;          /* sizeof(unsigned long) */
    unsigned char  ull;         /* sizeof(unsigned long long) */
    unsigned char  vp;          /* sizeof(void*): pointer type */
} SystemDataTypeLengths;
/* struct to store lengths of various system data types --------------------*/

/* count the types ---------------------------------------------------------*/
SystemDataTypeLengths system_data_type_lengths_get(void);
/* count the types ---------------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
void system_lengths_test(void);
/* test area ---------------------------------------------------------------*/

#endif  /* widths_h_ */
