#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include<sys/socket.h>
#include<netdb.h>

typedef struct  t_struc
{
    char    **arg;
    int     packet_send;
    int     packet_recv;
    float   time_min;
    float   time_max;
    float   *all_time;
    bool    verbose;
}       struc;

long     hxtoi(char* str);
void    help_option(void);
void    is_an_ip(char **arg, char **str);
void    free_arg(char **argv, int error);
void    verbose_option(char *ip, bool verbose);
void    init_struc(struc *global, char **argv, int argc, bool verbose);
bool    find_option(char **argv, char *opt);
char**  update(char **argv, int *argc, bool verbose);
char*   hostname_to_ip(char * hostname);

#endif