#ifndef _BUILT_IN_H_
#define _BUILT_IN_H_

typedef void (*CMD_HANDLER)();

typedef struct builtin_cmd  
{
	char *name;
	CMD_HANDLER handler;

} BUILTIN_CMD;

int builtin(void);

#endif