#include "ft_ping.h"

struc global;

void	endProg(int signal)
{
	if (signal == SIGINT)
	{
        pthread_join(*global.thread, NULL);
        printf("--- %s ping statistics ---\n", *global.arg);
        printf("%d packets transmitted, %d packets received", global.packet_send, global.packet_recv);
        printf(", %d%% packet loss\n", pourcent(global.packet_recv, global.packet_send));
        if (global.time[0] != -1)
            printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", global.time_min, moy(global.time), global.time_max, deviation(global.time));
        for(int i = 1; global.arg[i]; i++)
        {
            free(global.ip);
            is_an_ip(&global, global.arg[i]);
            verbose_option(global, global.arg[i]);
            printf("--- %s ping statistics ---\n", global.arg[i]);
            printf("1 packets transmitted, 0 packets received, 100%% packet loss\n");
        }
        free_arg(&global, 0);
		exit (0);
	}
}

void    loop(struc *global)
{
    gettimeofday(&global->start, NULL);
    send_packet(global);
    pthread_create(global->thread, NULL, recv_packet, (void *)global);
    pthread_join(*global->thread, NULL);
    sleep(1);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("./ft_ping: missing host operand\nTry './ft_ping -?' for more information.\n");
        return 1;
    }
    find_option(&global, argv);
    if (global.help == true)
        help_option();
    init_struc(&global, argv, argc);
    signal(SIGINT, &endProg);
    is_an_ip(&global, *global.arg);
    verbose_option(global, *global.arg);
    create_packet(&global);
    while(true)
        loop(&global);
    free_arg(&global, 0);
    close(global.sockfd);
    return 0;
}
