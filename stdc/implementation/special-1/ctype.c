
#include <ctype.h>



int
tolower (int c)
{
  if('A'<=c && c<='Z')
  {
  	return c-'A'+'a';
  }else{
  	return c;
  }
}

int
toupper (int c)
{
  if('a'<=c && c<='z')//islower
  {
  	return c-'a'+'A';
  }else{
  	return c;
  }
}
