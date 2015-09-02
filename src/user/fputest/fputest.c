#include <stdio.h>

#define CYLCES 100000

int main() {
	volatile double q = 0.0;
	for (int c = 0; c < CYLCES; ++c) {
		for (int i = 0; i < CYLCES; ++i) {
			q += 1.0;
		}
		for (int i = 0; i < CYLCES; ++i) {
			q -= 1.0;
		}
		if (q != 0.0) {
			printf("FPU Error: q=%f\n", q);
		}
	}
	return 0;
}