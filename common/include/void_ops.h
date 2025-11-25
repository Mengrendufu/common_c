#ifndef void_ops_h_
#define void_ops_h_

#include <stdint.h>
typedef uint64_t Type_PtrLength;
#define ALIGN_PTR_LEN(e_)  ((Type_PtrLength)(e_))
#define VOID_CAST(e_)      ((void *)(e_))

#endif  /* void_ops_h_ */
