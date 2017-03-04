
#ifndef signal_h__
#define signal_h__

#define SIG_DFL
#define SIG_ERR
#define SIG_IGN

#define SIGABRT
#define SIGFPE
#define SIGILL
#define SIGINT
#define SIGSEGV
#define SIGTERM



void (*signal(int sig,void (*handler)(int)))(int); //return the handler
int raise(int sig);


#endif //signal_h__