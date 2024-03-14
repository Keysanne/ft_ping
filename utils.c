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
    global->packet_recv = 0;
    global->packet_send = 0;
    global->time_min = 2147483648;
    global->time_max = 0;
    global->time = malloc(sizeof(float));
    global->time[0] = -1;
    /*-------------------SET-UP-RAW-SOCKET-------------------*/
    global->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (global->sockfd == -1)
    {
        perror("socket");
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