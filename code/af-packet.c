#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <netinet/in.h>

int main(void)
{
	int fd;
	int nbytes;
	int rc;
	char buf[1000];

	fd = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
	if (fd < 0) {
		perror("socket");
		return 1;
	}
	nbytes = read(fd, buf, 1000);
	if (nbytes < 0) {
		perror("read");
		close(fd);
		return 1;
	}
	if (nbytes == 0) {
		printf("no bytes\n");
		close(fd);
		return 1;
	}
	printf("saw %d bytes\n", nbytes);
	close(fd);
	return 0;
}
