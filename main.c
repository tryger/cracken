#include <stdio.h>
#include <getopt.h>
#include <string.h>

char *prnt;
char *hash;
char *dict_file;
int work_count;

int main(int argc, char *argv[])
{
	char c, t;

	while((c = getopt(argc, argv, "sch:f:p:n:")) != -1) {
		if (c == 'h') {
			hash = malloc(32);
			hash = optarg;
		}
		else if (c == 'f') {
			dict_file = (char *)malloc(strlen(optarg));
			dict_file = optarg;
		}
		else if (c == 's') {
			t = 1;
		}
		else if (c == 'c'){
			t = 0;
		}
		else if (c == 'p') {
			prnt = optarg;
		}
		else if (c == 'n'){
			work_count = atoi(optarg);
		}
	}

	if(t)
		node_root_loop();
	else
		node_smpl_loop();

	free(hash);
	free(dict_file);
	
	return 0;
}
