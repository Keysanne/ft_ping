#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void free_arg(char **argv, int error);
bool find_option(char **argv, char *opt);
char **update(char **argv, int *argc, bool verbose, bool help);

#endif