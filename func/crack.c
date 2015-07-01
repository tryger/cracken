int crackhash(char *hash, char *dict[], int len, int alg)
{
	char buf[32];

	while(len-- > 0) {
		md5(dict[len], &buf);
		if(!strncmp(&buf, hash, 32))
			return len;
	}
	return -1;
}
