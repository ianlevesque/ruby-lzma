#include "ruby.h"
#include "lzmalib.h"
#include "stdlib.h"

VALUE cLZMA;

static VALUE lz_compress(VALUE self, VALUE data) {
	VALUE result = Qnil;
	
	if(data != Qnil) {
		void *data_ptr = RSTRING_PTR(data);
		int data_len = RSTRING_LEN(data);
			
		int out_size;
		void *out_buffer = lzma_compress(data_ptr, data_len, &out_size);

		if(out_buffer) {
		  result = rb_str_new((char*)out_buffer, out_size);
			lzma_free(out_buffer);
		}
	}
	
	return result;
}

static VALUE lz_decompress(VALUE self, VALUE data) {
	VALUE result = Qnil;
	
	if(data != Qnil) {
		void *data_ptr = RSTRING_PTR(data);
		int len = RSTRING_LEN(data);
		
		int out_size;
		void *out_buffer = lzma_decompress(data_ptr, len, &out_size);
		
		if(out_buffer) {
			result = rb_str_new((char*)out_buffer, out_size);
			lzma_free(out_buffer);
		} else {
			rb_raise(rb_eRuntimeError, "Couldn't decompress with LZMA");
		}
	}
	
	return result;
}

extern "C" void Init_lzma_ruby() {
  cLZMA = rb_define_class("LZMA", rb_cObject);
  rb_define_method(cLZMA, "compress", (VALUE(*)(...))lz_compress, 1);
  rb_define_method(cLZMA, "decompress", (VALUE(*)(...))lz_decompress, 1);
}
