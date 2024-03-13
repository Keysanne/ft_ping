#include "ft_ping.h"

int malloc_size(char **argv)
{
    int x = 0;
    for(int y = 1; argv[y]; y++)
        if(argv[y][0] != '-')
            x++;
    return x;
}

char **update(char **argv)
{
    int j = 0;
    char **final = malloc((malloc_size(argv) + 2) * sizeof(char*));
    
    for(int i = 1; argv[i]; i++)
    {
        if (strncmp(argv[i], "-", 1) == 0)
            continue;
        else
            final[j++] = strdup(argv[i]);
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

void    init_struc(struc *global, char **argv)
{
    /*-------------------VAR-------------------*/
    global->id = getpid();
    global->arg = update(argv);
    global->packet_recv = 0;
    global->packet_send = 0;
    global->time_min = 2147483648;
    global->time_max = 0;
    global->time = malloc(sizeof(float));
    global->time[0] = -1;
    /*-------------------SET-UP-RAW-SOCKET-------------------*/
    global->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (global->sockfd == -1)
        perror("socket");
    return;
}

void find_option(struc *global, char **argv)
{
    char    options[] = "v?";
    for(int i = 1; argv[i]; i++)
    {
        if (argv[i][0] == '-')
        {
            for(int x = 1; argv[i][x]; x++)
            {
                if(find(options, argv[i][x]) == -1)
                {
                    if(printf("./ft_ping invalid option - '%c'\nTry './ft_ping -?' for more informations.\n", argv[i][x])) //change msg
                        exit(1);
                }
                else 
                {   
                    if (argv[i][x] == 'v')
                        global->verbose = true;
                    if (argv[i][x] == '?')
                        global->help = true;
                }
            }
        }
    }
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