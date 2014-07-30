#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char **argv){
	while(1) asm("int $0x80");
    return 0;
}