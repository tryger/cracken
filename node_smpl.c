#include "func/packet.h"
#include "func/net.h"

extern int work_count;

int node_smpl_loop()
{
	char **dict = malloc(work_count * sizeof(char *));
	char *hash;
	int sockd, i;
	u_short count;

	//registerme(sockd, NODETYPE_USER);

 	gethash(&hash);

	printf("Cracking %s ...\n\n", hash);

	do {
		dict = malloc(work_count * sizeof(char *));
		count = getwork(work_count, dict);
		printf("Got %d tries...\t%s\n", count, dict[0]);

	} while((i = crackhash(hash, dict, count, 0)) == -1); //md5

	solved(hash, dict[i]);

	printf("\nCRACKED!!\n%s\n", dict[i]);

	free(hash);
}
