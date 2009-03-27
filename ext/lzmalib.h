/*************************************************************************************************
 * A thin wrapper library of LZMA
 *************************************************************************************************/
 

#ifndef _LZMALIB_H                       /* duplication check */
#define _LZMALIB_H

#if defined(__cplusplus)
#define __LZMALIB_CLINKAGEBEGIN extern "C" {
#define __LZMALIB_CLINKAGEEND }
#else
#define __LZMALIB_CLINKAGEBEGIN
#define __LZMALIB_CLINKAGEEND
#endif
__LZMALIB_CLINKAGEBEGIN


#include <stdlib.h>



/*************************************************************************************************
 * API
 *************************************************************************************************/


/* Compress a serial object with LZMA encoding.
   `ptr' specifies the pointer to the region.
   `size' specifies the size of the region.
   `sp' specifies the pointer to the variable into which the size of the region of the return
   value is assigned.
   If successful, the return value is the pointer to the result object, else, it is `NULL'.
   Because the region of the return value is allocated with the `malloc' call, it should be
   released with the `free' call when it is no longer in use. */
void *lzma_compress(const void *ptr, int size, int *sp);


/* Decompress a serial object compressed with LZMA encoding.
   `ptr' specifies the pointer to the region.
   `size' specifies the size of the region.
   `sp' specifies the pointer to a variable into which the size of the region of the return
   value is assigned.
   If successful, the return value is the pointer to the result object, else, it is `NULL'.
   Because an additional zero code is appended at the end of the region of the return value,
   the return value can be treated as a character string.  Because the region of the return
   value is allocated with the `malloc' call, it should be released with the `free' call when it
   is no longer in use. */
void *lzma_decompress(const void *ptr, int size, int *sp);


/* Free a region on memory.
   `ptr' specifies the pointer to the region.  If it is `NULL', this function has no effect.
   Although this function is just a wrapper of `free' call, this is useful in applications using
   another package of the `malloc' series. */
void lzma_free(void *ptr);



__LZMALIB_CLINKAGEEND
#endif                                   /* duplication check */


/* END OF FILE */
