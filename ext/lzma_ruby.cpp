#include "ruby.h"
#include "lzmalib.h"

VALUE cLZMA;

static VALUE lz_compress(VALUE data) {
	VALUE result = Qnil;
	
	if(data != Qnil) {
		void *data_ptr = RSTRING_PTR(data);
		int data_len = RSTRING_LEN(data);
		
		int out_size;
		void *out_buffer = lzma_compress(data_ptr, data_len, &out_size);

		if(out_buffer)
		  result = rb_str_new((char*)out_buffer, out_size);
	}
	
	return result;
}

static VALUE lz_decompress(VALUE data) {
	VALUE result = Qnil;
	
	if(data != Qnil) {
		void *data_ptr = RSTRING_PTR(data);
		int len = RSTRING_LEN(data);
		
		int out_size;
		void *out_buffer = lzma_decompress(data_ptr, len, &out_size);
		
		if(out_buffer) {
			result = rb_str_new((char*)out_buffer, out_size);
		}
	}
	
	return result;
}

extern "C" void Init_lzma_ruby() {
  cLZMA = rb_define_class("LZMA", rb_cObject);
  rb_define_method(cLZMA, "compress", (VALUE(*)(...))lz_compress, 1);
  rb_define_method(cLZMA, "decompress", (VALUE(*)(...))lz_decompress, 1);
}
