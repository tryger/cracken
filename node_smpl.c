#include "func/packet.h"
#include "func/net.h"

#define DEF_COUNT 500 // just for test

int node_smpl_loop()
{
	char **dict = malloc(DEF_COUNT * sizeof(char *));
	char *hash;
	int sockd, i;
	u_short count;

	//sockd = raw_connect(prnt, 7070);

	//registerme(sockd, NODETYPE_USER);

 	gethash(/*sockd, */&hash);

	printf("Cracking %s ...\n\n", hash);

	do {
		count = getwork(/*sockd, */DEF_COUNT, dict);
		printf("Got %d tries...\t%s\n", count, dict[0]);

	} while((i = crackhash(hash, dict, count, 0)) == -1); //md5

	solved(/*sockd, */hash, dict[i]);

	printf("\nCRACKED!!\n%s\n", dict[i]);

	//raw_close(sockd);

	free(hash);
}
