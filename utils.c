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
            final[j++] = strdup(argv[i]);
    }
    final[j] = 0;
    return final;
}

void    init_struc(struc *global, char **argv, int argc, bool verbose)
{
    global->arg = update(argv, &argc, verbose);
    global->packet_recv = 0;
    global->packet_send = 0;
    return;
}

bool find_option(char **argv, char *opt)
{
    for(int i = 0; argv[i];i++)
        if (strcmp(argv[i], opt) == 0)
            return true;
    return false;
}

void free_arg(char **argv, int error)
{
    for(int i = 0; argv[i]; i++)
        free(argv[i]);
    free(argv);
    exit(error);
}