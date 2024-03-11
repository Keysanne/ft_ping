#ifndef FT_PING_H
# define FT_PING_H

#include <time.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <linux/if_packet.h>

typedef struct  t_struc
{
    char    **arg;
    int     sockfd;
    bool    verbose;
    float   time_min;
    float   time_max;
    float   *all_time;
    char    buffer[64];
    int     packet_send;
    int     packet_recv;
    struct icmphdr *icmp;
}       struc;

void    help_option(void);
void    free_arg(struc *global, int error);
void    is_an_ip(struc *global, char **str);
void    create_icmp(struc *global, int seq);
void    verbose_option(char *ip, bool verbose);
void    init_struc(struc *global, char **argv, int argc, bool verbose);
char**  update(char **argv, int *argc, bool verbose);
bool    find_option(char **argv, char *opt);
char*   hostname_to_ip(char * hostname);
long     hxtoi(char* str);

#endif