#include "ft_ping.h"

char **update(int argc, char **argv)
{
    int j = 0;
    char **final = calloc(argc, sizeof(char*));
    
    for(int i = 1; argv[i]; i++)
    {
        if (strncmp(argv[i], "-", 1) == 0)
            continue;
        else
            final[j++] = strdup(argv[i]);
    }
    return final;
}

void    init_struc(struc *global, char **argv, int argc)
{
    /*-------------------VAR-------------------*/
    global->id = getpid();
    global->arg = update(argc, argv);
    if (*global->arg == NULL)
    {
        printf("./ft_ping: missing host operand\nTry './ft_ping -?' for more information.\n");
        free_arg(global, 2);
    }
    global->packet_recv = 0;
    global->packet_send = 0;
    global->time_min = 2147483648;
    global->time_max = 0;
    global->time = malloc(sizeof(float));
    global->time[0] = -1;
    global->thread = calloc(1, sizeof(pthread_t));
    /*-------------------SET-UP-RAW-SOCKET-------------------*/
    global->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (global->sockfd == -1)
    {
        perror("socket");
        free_arg(global, 1);
    }
    struct timeval  timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    if (setsockopt(global->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    {
        perror("sockopt recv timeout");
        free_arg(global, 1);
    }
    int x = TTL;
    if (setsockopt(global->sockfd, IPPROTO_IP, IP_TTL, &x, sizeof(TTL)) < 0)
    {
        perror("sockopt ttl");
        free_arg(global, 1);
    }
    return;
}

void find_option(struc *global, char **argv)
{
    char    options[] = "v?";
    for(int i = 1; argv[i]; i++)
    {
        if (argv[i][0] == '-')
        {
            if (argv[i][1] == '\0')
            {
                printf("./ft_ping invalid option - '%c'\nTry './ft_ping -?' for more informations.\n", argv[i][1]);
                exit(1);
            }
            else
            {
                for(int x = 1; argv[i][x]; x++)
                {
                    if(find(options, argv[i][x]) == -1)
                    {   
                        printf("./ft_ping invalid option - '%c'\nTry './ft_ping -?' for more informations.\n", argv[i][x]);
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
}

void free_arg(struc *global, int error)
{
    for(int i = 0; global->arg[i]; i++)
        free(global->arg[i]);
    free(global->time);
    free(global->ip);
    free(global->arg);
    free(global->thread);
    close(global->sockfd);
    exit(error);
}

int   pourcent(float rec, float snd)
{
    float   mtp = 0;

    mtp = 100 / snd;
    int final = rec * mtp;
    return abs(final - 100);
}
