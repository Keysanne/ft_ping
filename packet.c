#include "ft_ping.h"

uint16_t checksum(unsigned char* buffer, int bytes)
{
	uint16_t	*buff;
	uint32_t	sum;

	buff = (uint16_t *)buffer;
	for (sum = 0; bytes > 1; bytes -= 2)
		sum += *buff++;
	if (bytes == 1)
		sum += *(uint8_t*)buff;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	return (~sum);
}

int    send_packet(struc *global)
{
    int     x;

    bzero(&global->dst, sizeof(global->dst));
    global->dst.sin_family = AF_INET;
    global->dst.sin_addr.s_addr = inet_addr(global->ip);
    global->dst.sin_port = 0;

    global->icmp.type = 8;
    global->icmp.code = 0;
    global->icmp.ident = htons(global->id);
    global->icmp.seq = htons(global->packet_send);
    bzero(&(global->icmp.buffer), sizeof(global->icmp.buffer));
    global->icmp.checksum = htons(checksum((unsigned char *)&(global->icmp.buffer), sizeof(global->icmp.buffer)));
    if((x = sendto(global->sockfd, &(global->icmp), sizeof(global->icmp), 0, (struct sockaddr*)&global->dst, sizeof(global->dst))) <= 0)
    {
        perror("sendto");
        free_arg(global, 1);
    }
    return x;
}

int     recv_packet(struc *global)
{
    int         x;
    char        buffer[64];    
    socklen_t   fromlen = sizeof(global->from);

    bzero(&global->from, sizeof(global->from));
    global->from.sin_family = AF_INET;
    global->from.sin_addr.s_addr = inet_addr(global->ip);
    global->from.sin_port = 0;
    if ((x = recvfrom(global->sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&global->from, &fromlen)) <= 0)
    {
        perror("recvfrom");
        free_arg(global, 1);
    }
    (global->packet_recv)++;
    return x;
}