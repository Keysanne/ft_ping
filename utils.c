#include "ft_ping.h"


char **update(char **argv, int *argc, bool verbose)
{
    int j = 0;
    char **final = malloc(((*argc) + 1 - (int)verbose) * sizeof(char*));
    
    (*argc)--;
    for(int i = 1; argv[i];i++)
    {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-?") == 0)
        {
            (*argc)--;
            continue;
        }
        else
        {
            if(argv[i][0] == '-')
            {
                final[j] = 0;
                printf("./ft_ping invalid option - '%s'\nTry './ft_ping -?' for more informations.\n", &argv[i][1]);
                for (int x = 0; final[x]; x++)
                    free(final[x]);
                free(final);
                exit(1);
            }
            else
                final[j++] = strdup(argv[i]);
        }
    }
    final[j] = 0;
    return final;
}

void    create_icmp(struc *global, int seq)
{
    struct icmphdr *icmp = (struct icmphdr *)global->buffer;
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0; 
    icmp->un.echo.id = getpid();
    icmp->un.echo.sequence = seq;
}

void    init_struc(struc *global, char **argv, int argc, bool verbose)
{
    /*-------------------VAR-------------------*/
    global->arg = update(argv, &argc, verbose);
    global->packet_recv = 0;
    global->packet_send = 0;
    /*-------------------SENDTO-VAR-------------------*/
    bzero(&global->dst, sizeof(global->dst));
    global->dst.sin_family = AF_INET;
    global->dst.sin_port = htons(1025);
    /*-------------------ICMP_PROTOCOL-------------------*/
    global->icmp = (struct icmphdr *)global->buffer;
    global->icmp->type = ICMP_ECHO;
    global->icmp->code = 0;
    global->icmp->checksum = 0;
    global->icmp->un.echo.sequence = htons(1);
    /*-------------------SET-UP-RAW-SOCKET-------------------*/
    global->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (global->sockfd == -1)
        perror("Error creating socket");
    return;
}

bool find_option(char **argv, char *opt)
{
    for(int i = 0; argv[i];i++)
        if (strcmp(argv[i], opt) == 0)
            return true;
    return false;
}

void free_arg(struc *global, int error)
{
    for(int i = 0; global->arg[i]; i++)
        free(global->arg[i]);
    free(global->arg);
    close(global->sockfd);
    exit(error);
}