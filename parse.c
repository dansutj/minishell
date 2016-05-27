#include <stdio.h>
#include "builtin.h"
#include "parse.h"
#include "externs.h"
#include "init.h"
#include "execute.h"

void get_command(int i);
void getname(char *name);
void print_command(void);


void shell_loop(void)
{
	while(1)
	{
		//初始化环境 
		init();

		//获取命令
		if(read_command() == -1)
			break;

		parse_command();

		execute_command();
	}

	printf("\nexit\n");
}

int read_command(void)
{
	//按行读取命令, cmdline包含\n字符
	if(fgets(cmdline, 1024, stdin) == NULL)
		return -1;

	return 0;

}


/*
 * 解析命令
 * 成功返回解析到的命令个数, 失败返回-1
 */
int parse_command(void)
{
	if(check("\n"))
		return 0;


	//判断是否内部命令并执行它
	if(builtin())
		return 0;

	/* 1. 解析第一条命令 */
	get_command(0);

	/* 2. 判定是否有输入重定向符 */
	if(check("<"))
	{
		getname(infile);
	}

	/* 3. 判定是否有管道 */
	int i;
	for(i = 1; i < PIPELINE; ++i)
	{
		if(check("|"))
			get_command(i);
		else 
			break;
	}

	/* 4. 判定是否有输出重定向符 */
	if(check(">"))
	{
		if(check(">"))
			append = 1;
		getname(outfile);
	}

	/* 5. 判定是否有后台作业 */
	if(check("&"))
		backgnd = 1;

	/* 6. 判定命令结束 */
	if(check("\n"))
	{
		cmd_count = i;
		return cmd_count;
	}
	else
	{
		fprintf(stderr, "Command line syntax error\n");
		return -1;
	}
	return 0;
	
}

int execute_command(void)
{
	//先判定是否内部命令

	execute_disk_command();
	return 0;
}

void print_command()
{
	int i;
	int j;
	printf("cmd_count = %d\n", cmd_count);

	if(infile[0] != '\0')
		printf("infile = [%s]\n", infile);

	if(outfile[0] != '\0')
		printf("outfile = [%s]\n", outfile);

	for(i = 0; i < cmd_count; ++i)
	{
		j = 0;
		while(cmd[i]. args[j] != NULL)
		{
			printf("[%s] ", cmd[i].args[j]);
			++j;
		}
		printf("\n");
	}
}

/*
 * 解析简单命令至cmd[i]
 * 提取cmdline中的命令参数到avline数组中
 * 并且将CMOMMAND结构中的args[]中的每个指针指向这些字符串
 */
void get_command(int i)
{
	int j = 0;
	int inword = 0;

	while(*lineptr != '\0')
	{
		while(*lineptr == ' ' || *lineptr == '\t')
			lineptr++;


		//将第i条命令第j个参数指向avptr
		cmd[i].args[j] = avptr;

		//参数提取致avptr指针所指向的数组avline
		while(*lineptr != '\0' && *lineptr != ' ' &&
			  *lineptr != '\t' && *lineptr != '<' &&
			  *lineptr != '>' && *lineptr != '|' &&
			  *lineptr != '&' && *lineptr != '\n')
		{
			*avptr++ = *lineptr++; 
			inword = 1;
		}
		*avptr++ = '\0';

		switch(*lineptr)
		{
			case ' ':
			case '\t':
				inword = 0;
				++j;
				break;

			case '<':
			case '>':
			case '|':
			case '&':
			case '\n':
				if(inword == 0)
					cmd[i].args[j] = NULL;
				return;

			default:
				return;
		}
	}
}

/*
 * 将lineptr中的字符串与str进行匹配
 * 成功返回1 lineptr移过所匹配的字符串
 * 失败返回0 lineptr保持不变
 */
int check(const char *str)
{
	char *p;
	while(*lineptr == ' ' || *lineptr == '\t')
		lineptr++;

	p = lineptr;
	while(*str != '\0' && *str == *p)
	{
		++str;
		++p;
	}

	if(*str == '\0')
	{
		lineptr = p; //移过所匹配的字符串
		return 1;
	}

	//lineptr保持不变
	return 0;
}

void getname(char *name)
{
	while(*lineptr == ' ' || *lineptr == '\t')
		++lineptr;

	while(*lineptr != '\0' && *lineptr != ' ' &&
		  *lineptr != '\t' && *lineptr != '<' &&
		  *lineptr != '>' && *lineptr != '|' &&
		  *lineptr != '&' && *lineptr != '\n')
	{
		*name++ = *lineptr++;
	}
	*name++ = '\0';
}






