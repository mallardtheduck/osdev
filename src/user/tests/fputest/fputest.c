#include <stdio.h>
#include <btos.h>

#define CYLCES 100000

int main(int argc, char **argv) {
	(void)argv;
	volatile double q = 0.0;
	for (int c = 0; c < 1000; ++c) {
		for (int i = 0; i < CYLCES; ++i) {
			q += 1.0;
		}
		bt_yield();
		for (int i = 0; i < CYLCES; ++i) {
			q -= 1.0;
		}
		if (q != 0.0) {
			printf("FPU Error: q=%f\n", q);
		}
	}
	
	double ans = 3.14 * argc;
	printf("FPU: %f\n", ans);
	return 0;
}