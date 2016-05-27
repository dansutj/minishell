#ifndef _PARSE_H_
#define _PARSE_H_

int read_command(void);
int parse_command(void);
int execute_command(void);
void shell_loop(void);
int check(const char *str);

#endif