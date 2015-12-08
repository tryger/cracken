#include "func/packet.h"
#include "func/net.h"
#include <stdio.h>

void *handle_request(void *);

FILE *dictp;
extern char *dict_file;

int node_root_loop()
{
	dictp = open_file(dict_file);

	raw_listen(&handle_request);

	close_file(dictp);
}

void *handle_request(void *desc)
{
	int sockd = ((struct client *)desc)->sockd;
	char *addr = &(((struct client *)desc)->addr);
	u_short port = ((struct client *)desc)->port;
	
	//check ip

	printf("THREAD:\n%d\n%s\n%d\n", sockd, addr, port);

	get_packet(sockd);

	printf("END THREAD\n\n");

	raw_close(sockd);

	pthread_exit(0);
}
