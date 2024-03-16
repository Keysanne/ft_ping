#include "ft_ping.h"

int    send_packet(struc *global)
{
    int         x;
    struct icmphdr *icmp = (icmphdr *)global->packet;
    icmp->un.echo.sequence = 0;
    icmp->code = 0;
    icmp->type = 8;
    icmp->un.echo.id = global->id;
    icmp->checksum = checksum((unisgned short *)icmp, sizeof(struct icmphdr));

    if((x = sendto(global->sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&global->dst, sizeof(global->dst))) <= 0)
    {
        perror("sendto");
        free_arg(global, 1);
    }
    (global->packet_send)++;
    return x;
}

int     recv_packet(struc *global)
{
    int         x;
    char        buffer[128];

    if ((x = recv(global->sockfd, buffer, sizeof(buffer), 0) < 0))
    {
        perror("recvfrom");
        free_arg(global, 1);
    }
    (global->packet_recv)++;
    return x;
}