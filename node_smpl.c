#include "func/packet.h"
#include "func/net.h"

#define DEF_COUNT 100 // just for test

int node_smpl_loop(char *hash, char *prnt)
{
	char **dict = malloc(DEF_COUNT * sizeof(char *));
	int sockd, i;
	u_short count;

	sockd = raw_connect(prnt, 7070);

	registerme(sockd, NODETYPE_USER);

	do {
		printf("sockd: %d\n", sockd);
		count = getwork(sockd, DEF_COUNT, dict);
		printf("\n%d\n", count);

	} while((i = crackhash(hash, dict, count, 0)) == -1); //md5

	printf("%s\n", dict[i]);

	raw_close(sockd);
}
