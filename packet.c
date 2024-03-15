#include "ft_ping.h"

int    send_packet(struc *global)
{
    int         x;
    libnet_t    *lnet;
    char        errbuf[LIBNET_ERRBUF_SIZE], payload[56];
    lnet = libnet_init(LIBNET_RAW4, "eth0", errbuf);
    //gestion erreur
    libnet_build_icmpv4_echo(8, 0, 0, global->id, global->packet_send + 1, (u_int8_t*)payload, sizeof(payload), lnet, 0);
    //gestion erreur
    u_int32_t target, source;
    target = libnet_name2addr4(lnet, global->ip, LIBNET_DONT_RESOLVE);
    source = libnet_get_ipaddr4(lnet);
    libnet_build_ipv4(LIBNET_IPV4_H + LIBNET_ICMPV4_ECHO_H + sizeof(payload), 0, global->id, 0, 64, IPPROTO_ICMP, 0, source, target, NULL, 0, lnet, 0);
    //gestion erreur

    if((x = sendto(global->sockfd, lnet, sizeof(lnet), 0, (struct sockaddr*)&global->dst, sizeof(global->dst))) <= 0)
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
    socklen_t   fromlen = sizeof(global->from);

    if ((x = recvfrom(global->sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&global->from, &fromlen)) <= 0)
    {
        perror("recvfrom");
        free_arg(global, 1);
    }
    (global->packet_recv)++;
    return x;
}