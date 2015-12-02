#include "func/packet.h"
#include "func/net.h"
#include <stdio.h>

void *handle_request(void *);

int node_root_loop()
{
	raw_listen(&handle_request);
}

void *handle_request(void *desc)
{
	int sockd = *(int *)desc;
	char buf[200];

	bzero(&buf, 200);
	raw_recv(sockd, &buf, 200);

	printf("%s", buf);
	printf("THREAD:\t%d\n", sockd);

	raw_recv(sockd, &buf, 200);

	raw_close(sockd);

	printf("END THREAD\n");

	pthread_exit(0);
}
