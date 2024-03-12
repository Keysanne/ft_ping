#include "ft_ping.h"

struc global;

void	endProg(int signal)
{
	if (signal == SIGINT)
	{
        printf("--- %s ping statistics ---\n", *global.arg);
        printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n", global.packet_send, global.packet_recv, (float)abs(global.packet_recv / global.packet_send * 100 - 100)); // mettre les %
        printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", global.time_min, moy(global.time), global.time_max, deviation(global.time));
        for(int i = 1; global.arg[i]; i++)
        {
            free(global.ip);
            is_an_ip(&global, global.arg[i]);
            verbose_option(global);
            printf("--- %s ping statistics ---\n", global.arg[i]);
            printf("1 packets transmitted, 0 packets received, 100%% packet loss\n");
        }
        free_arg(&global, 0);
		exit (0);
	}
}

void    loop(struc *global)
{
    int     x;
    clock_t start = clock();
    setup_icmp(global);


    if((x = sendto(global->sockfd, global->buffer, sizeof(global->buffer), 0, (struct sockaddr*)&global->dst, sizeof(global->dst))) < 0)
    {
        perror("Error sendto: ");
        free_arg(global, 1);
    }
    (global->packet_send)++;
    int     addrlen = sizeof(global->dst);
    if ((x = recvfrom(global->sockfd, global->buffer, sizeof(global->buffer), 0, (struct sockaddr*)&global->dst, &addrlen)) == -1)
    {
        perror("Error recvfrom: ");
        free_arg(global, 1);
    }
    (global->packet_recv)++;


    clock_t end = clock();
    float time = (end - start);
    time /= 1000;
    printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", x, global->ip, global->packet_send - 1, x, time);
    manage_time(global, time);
    sleep(1);
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
    is_an_ip(&global, *global.arg);
    verbose_option(global);
    while(true)
        loop(&global);
    free_arg(&global, 0);
    close(global.sockfd);
    return 0;
}