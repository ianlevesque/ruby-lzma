#include "ruby.h"
#include "LzmaEnc.h"
#include "LzmaDec.h"

VALUE cLZMA;

static void *SzAlloc(void *p, size_t size) { p = p; return malloc(size); }
static void SzFree(void *p, void *address) { p = p; free(address); }
static ISzAlloc alloc = { SzAlloc, SzFree };


static void lz_free(void *p) {
  vfaFreeBlobTracker(p);
}

static VALUE lz_compress(VALUE data) {
	void *data_ptr = RSTRING_PTR(data);
	long len = RSTRING_LEN(data);
	
	VALUE result = Qnil;
	
	CLzmaEncProps props;
	LzmaEncProps_Init(&props);
	
	Byte *outputBuffer = malloc(len + LZMA_PROPS_SIZE + 8)
	if(outputBuffer) {
		CLzmaEnc *p = (CLzmaEnc *)LzmaEnc_Create(alloc);
	  if (p) {
			res = LzmaEnc_SetProps(p, props);
		  if (res == SZ_OK) {
		    res = LzmaEnc_WriteProperties(p, outputBuffer, LZMA_PROPS_SIZE);
				
				for (i = 0; i < 8; i++)
			    outputBuffer[LZMA_PROPS_SIZE + i] = (Byte)(len >> (8 * i));
				
		    if (res == SZ_OK) {
					SizeT outLen = len - LZMA_PROPS_SIZE - 8;
		      res = LzmaEnc_MemEncode(p, outputBuffer + LZMA_PROPS_SIZE + 8, &outLen, data_ptr, len,
						0, 0, alloc, alloc);
					if(res == SZ_OK) {
						result = rb_str_new(outputBuffer, outLen);
					}
				}
		  }

			LzmaEnc_Destroy(p, alloc, allocBig);
		}
		
		free(outputBuffer)
	}
	
  return result;
}

static VALUE lz_decompress(VALUE data) {
	
}

void Init_lzma_ruby() {
  cLZMA = rb_define_class("LZMA", rb_cObject);
  rb_define_method(cBlobTrack, "compress", lz_compress, 1);
  rb_define_method(cBlobTrack, "decompress", lz_decompress, 1);
}
