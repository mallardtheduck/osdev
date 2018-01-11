#include <stdio.h>
#include <btos.h>
#include <dev/terminal.h>
#include <dev/terminal_ioctl.h>

bt_handle btos_get_handle(int fd);

int main(){
	bt_term_stdout();
	bt_term_ClearScreen();
    return 0;
}
