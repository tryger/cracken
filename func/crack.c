#include <stdlib.h>

int crackhash(char *hash, char *dict[], u_short len, int alg)
{
	char buf[33];
	int ret;

	while(len-- > 0) {
		md5(dict[len], &buf);
		if(!strncmp(&buf, hash, 32)) {
			ret = (int)len;
			goto end;
		}
	}
	ret = -1;
end:
	free(*dict);
	free(dict);
	return ret;
}
