
#ifndef string_h__
#define string_h__
#define NULL ((void*)0)
typedef unsigned int size_t;

//Starting with str_
char *strcpy(char *s,const char *ct);//ct-->s and return s
char *strncpy(char *s,const char *ct,size_t n);
char *strcat(char *s,const char *ct);
char *strncat(char *s,const char *ct,size_t n);
int strcmp(const char *cs,const char *ct);
int strncmp(const char *cs,const char *ct,size_t n);
char *strchr(const char *cs,int c);//tell c's position in cs
char *strrchr(const char *cs,int c);//last position
size_t strspn(const char *cs,const char *ct);//length of prefix of ct that appeared in cs
size_t strcspn(const char *cs,const char *ct);//length of prefix of ct that does appeared in cs
char *strpbrk(const char *cs,const char *ct);//return a pointer in ct,where the char there firstly appears in cs
char *strstr(const char *cs,const char *ct);
size_t strlen(const char *cs);
char *strerror(size_t n);//return string which error number n denotes
char *strtok(char *s,const char *ct);//continues call this function will go through every position that ct in s


//Starting with mem_
void *memcpy(char *,const char *ct,size_t n);
void *memmove(char *s,const char *ct,size_t n);
int memcmp(const char *cs,const char *ct,size_t n);//same with strcmp
void *memchr(const char *cs,int c,size_t n);//same with strchr
void *memset(char *s,int c,size_t n);

#endif //string_h__