#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <error.h>
#include <string.h>
#include <linux/netlink.h>

void main()
{
	int sk_fd = -1;
	size_t slen = 0;
    char i;
	char buf[4096];
    
	sk_fd = socket(AF_NETLINK, SOCK_RAW, 28);
	if (-1 == sk_fd)
	{
		perror("socket");
		return; 
	}

	memset(buf, 0, sizeof(buf));

    for (i = 0; i < 100; i ++)
    {
        buf[i] = i;
    }

	slen = send(sk_fd, buf, 100, 0);
	printf("%lu\r\n", slen);
	
	return;
}
