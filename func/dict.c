#include <stdio.h>
#include <sys/types.h>

FILE *open_file(char *file)
{
	FILE *f;

	if((f = fopen(file, "r")) < 0) {
		perror("fopen()");
		return -1;
	}
	return f;
}

u_long get_n_pass(FILE *fp, char **buf, u_short cnt)
{
	char *line;
	ssize_t i, len=0, count=0;
	u_long length = 0;

	while(count++ < cnt) {
		line = NULL;
		i = getline(&line, &len, fp);

		if(i != -1) {
			*buf = realloc(*buf, length + i);

			*(line + i - 1) = '\xff';

			strncpy(*buf + length, line, i);

			length += i;
		}

		free(line);
	}

	return length;
}

int close_file(FILE *fp)
{
	fclose(fp);
}
