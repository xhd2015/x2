#ifndef predefined_macros_h__
#define predefined_macros_h__

/*do not include this file,this is to be read*/
#if 0
/**
*when the preprocessor process include,it will push current values and change __FILE__ __LINE__ to match the actual values in included file.That means,you can always get the real value of one a file.
*/
#define __FILE__	/*expands to the name of current file,not the one #include does*/
#define __LINE__	/*expands to the current line number*/
#define __DATE__
#define __TIME__
#define __STDC__
#define __STDC_VERSION__	/*becomes to be a long integer like yyyymmL,such as 201103L*/
#define __STDC_HOSTED__		/*denotes whether the compiler's target is a hosted environment,which has a complete stdc library*/

/*You can use the following two macros to identify which compiler is used to process the header file*/
#define __cplusplus	/*when c++ compiler is used,this is defined,its values is similar with __STDC_VERSION__*/
#define __OBJC__	/*=1 if Obj-C compiler is used*/


#define __ASSEMBLER__	/*if preprocessing assembly language,it is 1*/

#define NDEBUG		/*if this is defined,assert will have a different behaviour*/
#endif //if 0

#endif //predefined_macros_h__