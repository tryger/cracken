#include <stdio.h>
#include <getopt.h>

char *prnt;
char *hash;

int main(int argc, char *argv[])
{
	char c, t;

	while((c = getopt(argc, argv, "sch:")) != -1) {
		if (c == 'h') {
			hash = malloc(32);
			hash = optarg;
		}
		else if (c == 's') {
			t = 1;
		}
		else if (c == 'c'){
			prnt = "127.0.0.1";
			t = 0;
		}
	}

	if(t)
		node_root_loop();
	else
		node_smpl_loop();

	free(hash);
	
	return 0;
}
