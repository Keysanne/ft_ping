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
            is_an_ip(&global, &global.arg[i]);
            verbose_option(global.arg[i], global.verbose);
            printf("--- %s ping statistics ---\n", global.arg[i]);
            printf("1 packets transmitted, 0 packets received, 100%% packet loss\n");
        }
        free_arg(&global, 0);
		exit (0);
	}
}


void    loop(struc *global)
{
    // create_icmp(global, global->packet_send + 1);
    clock_t start = clock();
    /*--------------------------------------------------------------------------*/
    struct sockaddr_in dst;
    memset((char *)&dst, 0, sizeof(dst));
    dst.sin_family = AF_INET;
    dst.sin_port = htons(1025);
    // struct icmphdr *icp = (struct icmphdr *)global->buffer;
    // icp->type = ICMP_ECHO;
    // icp->code = 0;
    // icp->checksum = 0;
    // icp->un.echo.sequence = htons(1);

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd == -1)
        perror("Error creating socket");
    ssize_t x = sendto(sockfd, global->buffer, sizeof(global->buffer), 0, (struct sockaddr*)&dst, sizeof(dst));
    perror("Error: ");
    printf("%zd bytes sent\n", x);
    (global->packet_send)++;
    /*--------------------------------------------------------------------------*/
    // struct sockaddr_in from;
    // unsigned int addrlen = sizeof(from);
    // to.sin_family = AF_INET;
    // to.sin_addr.s_addr = inet_addr(*global->arg);
    // x = recvfrom(sockfd, global->buffer, sizeof(global->buffer), 0, (struct sockaddr*)&from, &addrlen); 
    // printf("%zd\n", x);
    /*--------------------------------------------------------------------------*/
    (global->packet_recv)++;
    clock_t end = clock();
    float time = (end - start);
    time /= 1000;
    printf("%.3f\n", time);
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
    is_an_ip(&global, global.arg);
    verbose_option(*global.arg, global.verbose);
    while(true)
        loop(&global);
    free_arg(&global, 0);
    close(global.sockfd);
    return 0;
}

 // -v option 
    // int x = 7;
    // int *y = &x;
    // char *test;
    // sprintf(test, "%p", y);
    // test[6] = 0;
    // printf("%s\n", &test[2]);
    // get an hexa that is id and convert it to decimal to be prototype as hexa = deci