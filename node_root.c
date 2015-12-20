#include "func/packet.h"
#include "func/net.h"
#include <stdio.h>

void *handle_request(void *);

FILE *dictp;
extern char *dict_file;
extern char *hash;

int node_root_loop()
{
	printf("--- CRACKEN SERVER ---\n");
	printf("Hash: %s\n", hash);
	printf("Dict: %s\n", dict_file);

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

	printf("Serving %s:%d\n\n", addr, port);

	while(get_packet(sockd) == 0);

	raw_close(sockd);

	pthread_exit(0);
	//exit(0);
}
