#include "func/packet.h"
#include "func/net.h"
#include <stdio.h>

void *handle_request(void *);

int node_root_loop()
{
	// wait for connection
	raw_listen(&handle_request);

	// create thread handle_request()

	// send response
}

void *handle_request(void *desc)
{
	int sockd = *(int *)desc;
	char buf[200];

	
	raw_recv(sockd, &buf, 200);

	printf("%x\n", buf);


	raw_close(sockd);
}
