#include <sys/setjmp.h>

void longjmp(jmp_buf buf, int i) {
	(void)buf; (void)i;
}

void siglongjmp(sigjmp_buf buf, int i) {
	(void)buf; (void)i;
}
void _longjmp(jmp_buf buf, int i) {
	(void)buf; (void)i;
}

int setjmp(jmp_buf buf) {
	(void)buf;
	return 0;
}
int sigsetjmp(sigjmp_buf buf, int i) {
	(void)buf; (void)i;
	return 0;
}
int _setjmp(jmp_buf buf) {
	(void)buf;
	return 0;
}