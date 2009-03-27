#include "lzmalib.h"

#include "MyWindows.h"
#include "MyInitGuid.h"
#include "CommandLineParser.h"
#include "StringConvert.h"
#include "StringToInt.h"
#include "FileStreams.h"
#include "StreamUtils.h"
#include "LZMADecoder.h"
#include "LZMAEncoder.h"
#include "LzmaBench.h"
#include "LzmaRam.h"
#include <cstdlib>
#include <cstring>

extern "C" {
#include "LzmaRamDecode.h"
}

using namespace std;




/*************************************************************************************************
 * API
 *************************************************************************************************/


#define __LZMALIB_CLINKAGEBEGIN extern "C" {
#define __LZMALIB_CLINKAGEEND }
__LZMALIB_CLINKAGEBEGIN


/* Compress a serial object with LZMA encoding. */
void *lzma_compress(const void *ptr, int size, int *sp){
  size_t rsiz = size / 20 * 21 + (1 << 16) + 1;
  char* rbuf = (char*)malloc(rsiz);
  if(!rbuf) return NULL;
  size_t osiz;
  if(LzmaRamEncode((Byte*)ptr, size, (Byte*)rbuf, rsiz, &osiz,
                   1 << 23, SZ_FILTER_AUTO) != 0){
    free(rbuf);
    return NULL;
  }
  rbuf[osiz] = '\0';
  *sp = osiz;
  return rbuf;
}


/* Decompress a serial object compressed with LZMA encoding. */
void *lzma_decompress(const void *ptr, int size, int *sp){
  size_t rsiz;
  if(LzmaRamGetUncompressedSize((const unsigned char*)ptr, size, &rsiz) != 0) return NULL;
  char* rbuf = (char*)malloc(rsiz + 1);
  if(!rbuf) return NULL;
  size_t osiz;
  if(LzmaRamDecompress((const unsigned char*)ptr, size, (unsigned char*)rbuf, rsiz, &osiz,
                       malloc, free) != 0){
    free(rbuf);
    return NULL;
  }
  rbuf[osiz] = '\0';
  if(sp) *sp = osiz;
  return rbuf;
}


/* Free a region on memory */
void lzma_free(void *ptr){
  free(ptr);
}



__LZMALIB_CLINKAGEEND


/* END OF FILE */
