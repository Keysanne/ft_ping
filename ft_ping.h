#ifndef FT_PING_H
# define FT_PING_H

#include <time.h>
#include <math.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h> 
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <linux/if_packet.h>

typedef struct  t_struc
{
    int                 id;
    char                *ip;
    char                **arg;
    int                 sockfd;
    bool                verbose;
    float               time_min;
    float               time_max;
    float               *time;
    char                buffer[64];
    int                 packet_send;
    int                 packet_recv;
    struct icmphdr      *icmp;
    struct sockaddr_in  dst;
    struct sockaddr_in  from;
}       struc;

void    help_option(void);
void    setup_icmp(struc *global);
void    verbose_option(struc global, char *arg);
void    is_an_ip(struc *global, char *ip);
void    free_arg(struc *global, int error);
void    create_icmp(struc *global, int seq);
void    manage_time(struc *global, float time);
void    init_struc(struc *global, char **argv, int argc, bool verbose);

char**  update(char **argv, int *argc, bool verbose);

bool    find_option(char **argv, char opt);

char*   hostname_to_ip(char * hostname);

long    hxtoi(char* str);

float   moy(float *tab);
float   deviation(float *tab);

#endif