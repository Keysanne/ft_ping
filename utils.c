#include "ft_ping.h"

char **update(char **argv, int *argc, bool verbose)
{
    int j = 0;
    char **final = malloc(((*argc) + 1 - (int)verbose) * sizeof(char*));
    
    (*argc)--;
    for(int i = 1; argv[i];i++)
    {
        if (strncmp(argv[i], "-") == 0)
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

void    setup_icmp(struc *global)
{
    /*-------------------SENDTO-VAR-------------------*/
    bzero(&global->dst, sizeof(global->dst));
    global->dst.sin_family = AF_INET;
    global->dst.sin_addr.s_addr = inet_addr(global->ip);
    /*-------------------ICMP_PROTOCOL-------------------*/
    global->icmp = (struct icmphdr *)global->buffer;
    global->icmp->type = ICMP_ECHO;
    global->icmp->code = 0;
    global->icmp->checksum = 0;
    global->icmp->un.echo.sequence = 0;
}

void    init_struc(struc *global, char **argv, int argc, bool verbose)
{
    /*-------------------VAR-------------------*/
    global->id = getpid();
    global->arg = update(argv, &argc, verbose);
    global->packet_recv = 0;
    global->packet_send = 0;
    global->time_min = 2147483648;
    global->time_max = 0;
    global->time = malloc(sizeof(float));
    global->time[0] = -1;
    /*-------------------SET-UP-RAW-SOCKET-------------------*/
    global->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (global->sockfd == -1)
        perror("Error creating socket");
    return;
}

bool find_option(char **argv, char opt)
{
    for(int i = 0; argv[i];i++)
        if (argv[i][0] == '-')
            for(int j = 0;argv[i][j]; j++)
                if(argv[i][j] == opt)
                    return true;
    return false;
}

void free_arg(struc *global, int error)
{
    for(int i = 0; global->arg[i]; i++)
        free(global->arg[i]);
    free(global->time);
    free(global->ip);
    free(global->arg);
    close(global->sockfd);
    exit(error);
}