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

int	timer(long time_sec, long time_usec)
{
	struct timeval	test;
	int				sec;
	int				milli;

	gettimeofday(&test, NULL);
	sec = (test.tv_sec - time_sec) * 1000;
	milli = (test.tv_usec - time_usec) / 1000;
	return (sec + milli);
}

void    loop(struc *global)
{
	struct timeval	test;
	gettimeofday(&test, NULL);
    struct sockaddr_in *dst
     = calloc(sizeof(struct sockaddr_in), 0);
    dst->sin_family = AF_INET;
    dst->sin_port = htons(1025);
    if(sendto(global->sockfd, global->buffer, sizeof(global->buffer), 0, (struct sockaddr*)&dst, sizeof(*dst)) < 0)
        free_arg(global, 1);
    (global->packet_send)++;


    struct  msghdr  msg;
    char            addrbuf[128];
    struct iovec    iov;
    bzero(&msg, sizeof(msg));
    msg.msg_name = addrbuf;
    msg.msg_namelen = sizeof(addrbuf);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    if(recvmsg(global->sockfd, &msg, MSG_WAITALL) < 0)
        free_arg(global, 1);
    (global->packet_recv)++;
    
    
    printf("%d\n", timer(test.tv_sec, test.tv_usec));
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