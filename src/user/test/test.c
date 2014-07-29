#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(char **argv, int argc){
	asm("int $0x80");
	asm("cli; hlt");
    return 0;
}