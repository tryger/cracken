#include "func/packet.h"
#include "func/net.h"

extern int work_count;
extern char *prnt;

int node_smpl_loop()
{
	char **dict = malloc(work_count * sizeof(char *));
	char *hash;
	int sockd, i;
	u_short count;

	sockd = raw_connect(prnt, 7070);

	//registerme(sockd, NODETYPE_USER);

 	gethash(sockd, &hash);

	printf("Cracking %s ...\n\n", hash);

	do {
		dict = malloc(work_count * sizeof(char *));
		count = getwork(sockd, work_count, dict);

	} while((i = crackhash(hash, dict, count, 0)) == -1); //md5

	solved(sockd, hash, dict[i]);

	printf("\nCRACKED!!\n%s\n", dict[i]);

	free(hash);
	
	raw_close(sockd);
}
