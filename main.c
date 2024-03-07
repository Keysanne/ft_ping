#include "ft_ping.h"

int main(int argc, char **argv)
{
    bool verbose = find_option(argv,"-v");
    bool help = find_option(argv,"-?");
    argv = update(argv, &argc, verbose, help);
    if (argc != 1)
        if (printf("Error: you can provide only one IP\n"))
            free_arg(argv, 1);
    free_arg(argv, 0);
}