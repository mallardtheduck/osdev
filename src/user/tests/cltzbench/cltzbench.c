#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

uint64_t current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

int main(void){
	uint32_t i = 2;
	uint32_t c = i;
	uint64_t start = current_timestamp();
	while(i < 10000000){
		if(c == 1) c = ++i;
		if(c % 2) c = (3 * c) + 1;
		else c = c / 2;
	}
	uint64_t end = current_timestamp();
	uint64_t score = end - start;
	printf("Score: %llu (lower is better)\n", score);
	return 0;
}
