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
#include <linux/if_packet.h>
#include <libnet.h>


typedef struct  struc
{
    int                 id;
    bool                help;
    bool                verbose;
    int                 sockfd;

    char                *ip;
    char                **arg;
    
    float               *time;
    float               time_min;
    float               time_max;
    
    int                 packet_send;
    int                 packet_recv;
    struct sockaddr_in  dst;
    struct sockaddr_in  from;
}   struc;

void    help_option(void);
void    setup_icmp(struc *global);
void    find_option(struc *global, char **argv);
void    is_an_ip(struc *global, char *ip);
void    free_arg(struc *global, int error);
void    manage_time(struc *global, float time);
void    verbose_option(struc global, char *arg);
void    init_struc(struc *global, char **argv, int argc);

int     malloc_size(char **argv);
int     find(char* str, char find);
int     send_packet(struc *global);
int     recv_packet(struc *global);

char**  update(int argc, char **argv);

char*   hostname_to_ip(char * hostname);

long    hxtoi(char* str);

float   moy(float *tab);
float   deviation(float *tab);

#endif