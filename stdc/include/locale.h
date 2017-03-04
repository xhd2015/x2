
#ifndef locale_h__
#define locale_h__

//these macros are used in the two functions listed below
#define	LC_ALL
#define LC_COLLATE
#define LC_CTYPE
//currency
#define LC_MONETARY
#define LC_NUMERIC

//strftime
#define LC_TIME
typedef struct{
   char *decimal_point;
   char *thousands_sep;
   char *grouping;	
   char *int_curr_symbol;
   char *currency_symbol;
   char *mon_decimal_point;
   char *mon_thousands_sep;
   char *mon_grouping;
   char *positive_sign;
   char *negative_sign;
   char int_frac_digits;
   char frac_digits;
   char p_cs_precedes;
   char p_sep_by_space;
   char n_cs_precedes;
   char n_sep_by_space;
   char p_sign_posn;
   char n_sign_posn;
} lconv;

char *setlocale(int category,const char *locale);
lconv *localeconv(void);

#endif //locale_h__