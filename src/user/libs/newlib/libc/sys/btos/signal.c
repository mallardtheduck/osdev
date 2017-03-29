#include <signal.h>
#include <sys/setjmp.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) { return -1; }
int sigprocmask(int how, const sigset_t *set, sigset_t *oset) { return -1; }
_sig_func_ptr signal (int i, _sig_func_ptr p) { return SIG_ERR; };
int raise(int sig) { return -1; }
void siglongjmp(sigjmp_buf env, int val) {};
int sigsetjmp(sigjmp_buf env, int savemask) { return 0; }
