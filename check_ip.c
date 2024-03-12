#include "ft_ping.h"

void    is_an_ip(struc *global, char *ip)
{
    struct sockaddr_in sa;

	global->ip = strdup(ip);
    if (inet_pton(AF_INET, global->ip, &(sa.sin_addr)) == 1)
        return;
    else
    {
        if (strncmp(global->ip, "0x", 2) == 0)
            sprintf(global->ip, "%ld", hxtoi(global->ip));
        global->ip = hostname_to_ip(global->ip);
        if (inet_pton(AF_INET, global->ip, &(sa.sin_addr)) == 1)
            return;
        printf("./ft_ping: Unknown host\n");
        free_arg(global, 1);
    }
}

int find(char* str, char find)
{
	for(int i = 0; str[i]; i++)
		if (str[i] == find)
			return i;
	return -1;
}

long hxtoi(char* str)
{
	long		x = 0, y = 0, rst = 0; 
	char	*base[] = {"0123456789abcdef", "0123456789ABCDEF"};

	for(int i = 2; str[i]; i++)
	{
		rst *= 16;
		if ((x = find(base[0], str[i])) == -1 && (y = find(base[1], str[i])) == -1)
			return -1;
		rst += x > y ? x : y;
	}
	return rst;
}

char* hostname_to_ip(char * hostname)
{
	struct hostent	*host = gethostbyname(hostname);

	free(hostname);
	if (host == NULL)
		return strdup("");
    return strdup(inet_ntoa(**(struct in_addr **)host->h_addr_list));
}