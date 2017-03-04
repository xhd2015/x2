
#ifndef ctype_h__
#define ctype_h__

int isalnum(int c);//c must be EOF(int) or unsiged char
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);

//Transfer
int tolower(int c);
int toupper(int c);




#endif //ctype_h__