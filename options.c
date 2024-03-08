#include "ft_ping.h"

void    help_option(void)
{
    printf("Usage: ./ft_ping [OPTION...] HOST ...\n");
    printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
    printf("Options valid for all request types:\n\n");
    printf("  -v,\tverbose output\n\n");
    printf("Options valid for --echo requests:\n\n");
    printf("  -?,\tgive this help list\n");
    exit(0);
}

void    verbose_option(char *ip, bool verbose)
{
    if (verbose == true)
        printf("PING %s (%s): 56 data bytes, id %d = %d\n", ip, ip, 10, 10); // CHANGE THE TWO 10
    else
        printf("PING %s (%s): 56 data bytes\n", ip, ip);
}