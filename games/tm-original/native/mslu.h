#ifndef TM_ORIGINAL_MSLU_H
#define TM_ORIGINAL_MSLU_H

#include "x86.h"

#ifdef __cplusplus
extern "C" {
#endif
void tm_original_mslu_get_proc_address(X86 *c);
#ifdef __cplusplus
}
#endif

#define FN_0040f92a tm_original_mslu_get_proc_address

#endif
