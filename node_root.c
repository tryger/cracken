#include "func/packet.h"
#include "func/net.h"
#include <stdio.h>

void *handle_request(void *);

FILE *dictp;

int node_root_loop()
{
	dictp = open_file("dict.txt");

	raw_listen(&handle_request);

	close_file(dictp);
}

void *handle_request(void *desc)
{
	int sockd = ((struct client *)desc)->sockd;
	char *addr = &(((struct client *)desc)->addr);
	u_short port = ((struct client *)desc)->port;
	char buf[MAX_PACKET_LEN];

	//check ip


//	bzero(&buf, MAX_PACKET_LEN);

	printf("THREAD:\n%d\n%s\n%d\n", sockd, addr, port);

	get_packet(sockd);
/*
	raw_recv(sockd, &buf, MAX_PACKET_LEN);
	printf("%s", buf);

	raw_recv(sockd, &buf, MAX_PACKET_LEN);

	raw_close(sockd);
*/
	printf("END THREAD\n");

	pthread_exit(0);
}
