#ifndef __Base64__
#define __Base64__

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
namespace Base64 {
	void build_decoding_table();
	char* base64_encode(const unsigned char* data, size_t input_length, size_t* output_length);
	unsigned char* base64_decode(const char* data, size_t input_length, size_t* output_length);
	void base64_cleanup();
}

#endif  __Base64__

