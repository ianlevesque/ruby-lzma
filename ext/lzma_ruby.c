#include "ruby.h"
#include "LzmaEnc.h"
#include "LzmaDec.h"

#include <stdio.h>

VALUE cLZMA;

static void *SzAlloc(void *p, size_t size) { p = p; return malloc(size); }
static void SzFree(void *p, void *address) { p = p; free(address); }
static ISzAlloc alloc = { SzAlloc, SzFree };


static void lz_free(void *p) {
  vfaFreeBlobTracker(p);
}

static VALUE lz_compress(VALUE data) {
	void *data_ptr = RSTRING_PTR(data);
	SizeT len = RSTRING_LEN(data);
	
	VALUE result = Qnil;
	
	CLzmaEncProps props;
	LzmaEncProps_Init(&props);
	
	Byte *outputBuffer = malloc(len + LZMA_PROPS_SIZE + 8);
	if(outputBuffer) {
		CLzmaEncHandle *p = LzmaEnc_Create(&alloc);
	  if (p) {
			SRes res = LzmaEnc_SetProps(p, &props);
		  if (res == SZ_OK) {
				SizeT propSize = LZMA_PROPS_SIZE;
		    res = LzmaEnc_WriteProperties(p, outputBuffer, &propSize);
		    if (res == SZ_OK) {
					int i;
					for (i = 0; i < 8; i++)
				    outputBuffer[LZMA_PROPS_SIZE + i] = (Byte)(len >> (8 * i));
					
					SizeT outLen = len;
		      res = LzmaEnc_MemEncode(p, outputBuffer + LZMA_PROPS_SIZE + 8, &outLen, data_ptr, len,
						0, 0, &alloc, &alloc);
					if(res == SZ_OK) {
						result = rb_str_new((char*)outputBuffer, outLen);
					} else {
						char message[100];
						snprintf(message, 100, "Couldn't encode with lzma (%i)", result);
						rb_raise(rb_eRuntimeError, message);
					}
				} else {
					rb_raise(rb_eRuntimeError, "Couldn't write lzma properties to output buffer");
				}
		  } else {
				rb_raise(rb_eRuntimeError, "Couldn't set default lzma properties");
			}

			LzmaEnc_Destroy(p, &alloc, &alloc);
		} else {
			rb_raise(rb_eRuntimeError, "Couldn't create lzma encoder");
		}
		
		free(outputBuffer);
	} else {
		rb_raise(rb_eRuntimeError, "Couldn't malloc output buffer");
	}
	
  return result;
}

static VALUE lz_decompress(VALUE data) {
	VALUE result = Qnil;
	
	if(data != Qnil) {
		Byte *data_ptr = (Byte*)RSTRING_PTR(data);
		SizeT len = RSTRING_LEN(data);
		if(len > LZMA_PROPS_SIZE + 8) {
			SizeT decomp_size_offset = LZMA_PROPS_SIZE;
			SizeT decompressedSize = data_ptr[decomp_size_offset + 1] | ((UInt32)data_ptr[decomp_size_offset + 2] << 8) | ((UInt32)data_ptr[decomp_size_offset + 3] << 16) | ((UInt32)data_ptr[decomp_size_offset + 4] << 24);
	
	  printf("Decomp size: %i", (int)decompressedSize);
	
		// Byte *outputBuffer = malloc(decompressedSize);
		// if(outputBuffer) {
		// 	
		// 	free(outputBuffer);
		// }
		}
	}
	
	return result;
}

void Init_lzma_ruby() {
  cLZMA = rb_define_class("LZMA", rb_cObject);
  rb_define_method(cLZMA, "compress", lz_compress, 1);
  rb_define_method(cLZMA, "decompress", lz_decompress, 1);
}
