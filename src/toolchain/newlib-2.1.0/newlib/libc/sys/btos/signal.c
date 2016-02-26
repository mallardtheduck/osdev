#include <signal.h>
#include <sys/setjmp.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {}
int sigprocmask(int how, const sigset_t *set, sigset_t *oset) {}
_sig_func_ptr signal (int i, _sig_func_ptr p) {};
int raise(int sig) {}