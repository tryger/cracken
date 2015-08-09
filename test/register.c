#include <stdio.h>

#include "../func/packet.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
		return -1;

	if(register_me(argv[1], NODETYPE_USER) == 0) {
		printf("SUCCESSFULLY REGISTERED!");
		return 0;
	} else {
		printf("PROBLEM WHILE REGISTERING!");
		return 1;
	}
}
