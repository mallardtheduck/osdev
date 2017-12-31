#include <btos_module.h>

struct cmdLine{
	char *cmd;
	size_t argc;
	char **argv;
};

cmdLine parse_cmd(const char *c);
void free_cmd(cmdLine c);
