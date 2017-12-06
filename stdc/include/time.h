
#ifndef time_h__
#define time_h__

#define NULL ((void*)0)
#define CLOCKS_PER_SEC
typedef unsigned int size_t;
typedef struct clock_t_struct{


}clock_t;

struct tm {
   int tm_sec;         /* seconds,  range 0 to 59          */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */
};	
typedef struct time_t_struct{

}time_t;


clock_t clock(void);
time_t time(time_t *tp);
double difftime(time_t time2,time_t time1);
time_t mktime(struct tm *tp);
char *asctime(const struct tm *tp);
char *ctime(const time_t *tp);
struct tm *gmtime(const time_t *tp);
size_t strftime(char *s,size_t smax,const char *fmt,const struct tm *p);



#endif //time_h__