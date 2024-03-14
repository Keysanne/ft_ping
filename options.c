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

void    verbose_option(struc global, char *arg)
{
    if (global.verbose == true)
        printf("PING %s (%s): %lu data bytes, id %x = %d\n", arg, global.ip, sizeof(global.icmp.buffer),global.id, global.id);
    else
        printf("PING %s (%s): %lu data bytes\n", arg, global.ip, sizeof(global.icmp.buffer));
}