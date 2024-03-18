#include "ft_ping.h"

unsigned short checksum(void* buffer, int bytes)
{
	unsigned short	*buff = buffer;
	unsigned int	sum;
    unsigned short    result;

	for (sum = 0; bytes > 1; bytes -= 2)
		sum += *buff++;
	if (bytes == 1)
		sum += *(unsigned char*)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
    result = ~sum;
	return result;
}

void    create_packet(struc *global)
{
    global->dst.sin_family = AF_INET;
    inet_aton(global->ip, &(global->dst.sin_addr));
    struct icmphdr *icmp = (struct icmphdr *)global->packet;
    icmp->un.echo.sequence = 0;
    icmp->code = 0;
    icmp->type = 8;
    icmp->un.echo.id = global->id;
    icmp->checksum = checksum((unsigned short *)icmp, sizeof(struct icmphdr));
}

int    send_packet(struc *global)
{
    int         x;

    if((x = sendto(global->sockfd, global->packet, sizeof(struct icmphdr), 0, (struct sockaddr*)&global->dst, sizeof(global->dst))) <= 0)
    {
        perror("sendto");
        free_arg(global, 1);
    }
    (global->packet_send)++;
    return x;
}

void     *recv_packet(void *data)
{
    struc           *global = data;
    char            buffer[64];
    struct timeval  end;

    while (true)
    {
        if (recv(global->sockfd, buffer, sizeof(buffer), 0) < 0)
            return NULL;
        struct icmphdr *icmp = (struct icmphdr*)(buffer + sizeof(struct iphdr));
        if (icmp->type == ICMP_ECHOREPLY)
        {
            gettimeofday(&end, NULL);
            double time = (end.tv_sec - global->start.tv_sec) * 1000.0; 
            time += (end.tv_usec - global->start.tv_usec) / 1000.0;
            printf("%ld bytes from %s: icmp_seq=%d ttl=%ld time=%.3f ms\n", sizeof(buffer), global->ip, global->packet_send - 1, sizeof(buffer), time);
            manage_time(global, time);
            (global->packet_recv)++;
            return NULL;
        }
    }
}
