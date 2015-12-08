#include <netinet/in.h>

struct client {
	int sockd;
	char addr[INET_ADDRSTRLEN];
	u_short port;
};

#define MAX_PACKET_LEN 200 // inventado
