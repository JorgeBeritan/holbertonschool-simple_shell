#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int _printenv(void);
char *get_envidia(const char *name);
char *command_path(char *cmd);
int command_read(char *s, size_t __attribute__((unused))file_stream);
int execute(char *cmd_arr[]);

#endif /* SHELL_H */
