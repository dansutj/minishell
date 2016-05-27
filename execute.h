#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include "externs.h"
#include "def.h"


void forkexec(int i);
int execute_disk_command(void);

#endif