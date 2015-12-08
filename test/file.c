#include <stdio.h>

int main()
{
	FILE *fp;
	char *data;

	fp = open_file("dict.txt");


	data = (char *)malloc(0);
	get_n_pass(fp, &data, 2);

	printf("%s\n", data);
	free(data);

	close_file(fp);
}
