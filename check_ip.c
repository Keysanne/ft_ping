#include "ft_ping.h"

void    is_an_ip(char **arg, char *ip)
{
    struct sockaddr_in sa;

    if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1)
        return;
    else
    {
        if (strncmp(ip, "0x", 2) == 0)
            sprintf(ip, "%d", hxtoi(ip));
        hostname_to_ip(ip, ip);
        if (inet_pton(AF_INET, ip, &(sa.sin_addr)) == 1)
            return;
        printf("./ft_ping: Unknown host\n");
        free_arg(arg, 1);
    }
}

int find(char* str, char find)
{
	for(int i = 0; str[i]; i++)
		if (str[i] == find)
			return i;
	return -1;
}

int hxtoi(char* str)
{
	int		rst = 0; 
	char	base[] = "0123456789abcdef";

	for(int i = 2;str[i]; i++)
	{
		rst *= 16;
		rst += find(base, str[i]);
	}
	return rst;
}

char* hostname_to_ip(char * hostname , char* ip)
{
	struct hostent	*he;
		
	if ((he = gethostbyname(hostname)) == NULL)
		return NULL;
	strcpy(ip , inet_ntoa(**(struct in_addr **)he->h_addr_list));
    return ip;
}