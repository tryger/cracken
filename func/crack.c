#include <stdlib.h>

int crackhash(char *hash, char *dict[], u_short len, int alg)
{
	char buf[33];

	while(len-- > 0) {
		md5(dict[len], &buf);
		if(!strncmp(&buf, hash, 32))
			return (int)len;
	}
	return -1;
}
