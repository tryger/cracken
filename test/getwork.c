#include <stdio.h>

#include "../func/packet.h"

main(int argc, char *argv[])
{
	char **dict;
	int i = 0, count = atoi(argv[2]);

	if(argc != 3) {
		printf("Usage: %s [parent ip] [count]\n", argv[0]);
		return -1;
	}

	getwork(argv[1], count, dict);

	while(i < count)
		printf("%d:\t%s\n", i, dict[i++]);
}
