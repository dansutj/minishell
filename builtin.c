#include "builtin.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

void do_exit(void);
void do_cd(void);
void do_type(void);


BUILTIN_CMD builtins[] = {
	{"exit", do_exit},
	{"cd", do_cd},
	{"type", do_type},
	{NULL, NULL}
};


/*
 * 内部命令解析
 * 返回1表示内部命令, 0表示外部命令
 */
int builtin(void)
{
	int i = 0;
	int found = 0;

	while(builtins[i].name != NULL)
	{
		if(check(builtins[i].name))
		{
			builtins[i].handler();
			found = 1;
			break;
		}
		++i;
	}

	return found;
}

void do_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void do_cd(void)
{
	printf("do cd...\n");
	exit(EXIT_SUCCESS);
}

void do_type(void)
{

}
