
#ifndef limits_h__
#define limits_h__

//these values are implementation related but cannot be less than the given value below
#define CHAR_BIT 8
#define SCHAR_MIN -128
#define SCHAR_MAX	+127

#define CHAR_MAX	+127
#define CHAR_MIN	-128
#define MB_LEN_MAX	16		//define the most number of bytes in multi-byte marchine
#define INT_MAX		+2147483647
#define INT_MIN		-2147483648

#define LONG_MAX	+9223372036854775807l
#define LONG_MIN	-9223372036854775808l
#define ULONG_MAX	18446744073709551615
#define SHRT_MAX	+32767
#define SHRT_MIN	-32768
#define UCHAR_MAX	255
#define UINT_MAX	4294967295
#define USHORT_MAX	65535

#endif //limits_h__