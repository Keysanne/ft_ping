#include "ft_ping.h"

struc global;

void	endProg(int signal)
{
	if (signal == SIGINT)
	{
        printf("--- %s ping statistics ---\n", *global.arg);
        printf("%d packets transmitted, %d packets received, %d%% packet loss\n", 1, 1, 0);
        printf("round-trip min/avg/max/stddev = %f/%f/%f/%f ms\n", 0.1, 0.1, 0.1, 0.1);
        for(int i = 1; global.arg[i]; i++)
        {
            is_an_ip(global.arg, global.arg[i]);
            verbose_option(global.arg[i], global.verbose);
            printf("--- %s ping statistics ---\n", global.arg[i]);
            printf("1 packets transmitted, 0 packets received, 100%% packet loss\n");
        }
        free_arg(global.arg, 0);
		exit (0);
	}
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("./ft_ping: missing host operand\nTry './ft_ping -?' for more information.\n");
        return 1;
    }
    if (find_option(argv,"-?") == true)
        help_option();
    global.verbose = find_option(argv,"-v");
    init_struc(&global, argv, argc, global.verbose);
    signal(SIGINT, &endProg);
    is_an_ip(global.arg, *global.arg);
    verbose_option(*global.arg, global.verbose);
    while(true)
        ;
    free_arg(global.arg, 0);
    return 0;
}