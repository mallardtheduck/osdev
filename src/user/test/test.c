#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char **argv){
	asm("int $0x80");
	asm("cli; hlt");
    return 0;
}