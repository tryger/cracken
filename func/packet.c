#include "packet.h"

#include <string.h>
#include <stdlib.h>

int fmt_work(char *, char **, u_char);

int send_packet(int sockd, void *packet)
{
/*	switch(*(char *)packet) {
		case OP_HI:
			send_hi_packet(dst, (struct hi_packet *) packet);
			break;
		case OP_GETW:
			send_getw_packet(dst, (struct getw_packet *) packet);
			break;
	}
*/
}

int send_hi_packet(int sockd, struct hi_packet *packet)
{
	char data[HI_LEN];

	if(fmt_packet(packet, &data, HI_LEN) != 0)
		return ERR_MALFORMEDPKT;

	if(raw_send(sockd, &data, HI_LEN) != HI_LEN)
		return -1;

	return HI_LEN;
}
int recv_hi_packet(int sockd, struct hi_packet *packet)
{
	char data[HI_LEN];

	if(raw_recv(sockd, &data, HI_LEN) != HI_LEN)
		return -1;

	if(fmt_packet(&data, packet, HI_LEN))
		return ERR_MALFORMEDPKT;

	return HI_LEN;
}


int send_getw_packet(int sockd, struct getw_packet *packet)
{
	char data[GETW_LEN];

	if(fmt_packet(packet, &data, GETW_LEN))
		return ERR_MALFORMEDPKT;

	return raw_send(sockd, &data, HI_LEN);
}
int recv_getw_packet(int sockd, struct getw_packet *packet, char **dict)
{
	char *data = malloc(GETW_LEN);

	if(raw_recv(sockd, data, HI_LEN) != HI_LEN)
		return -1;

	if(fmt_packet(data, packet, GETW_LEN))
		return ERR_MALFORMEDPKT;

	data = realloc(data, packet->length);

	if(raw_recv(sockd, data, packet->length) != packet->length)
		return -1;

	fmt_work(data, dict, packet->length);

	free(data);
}



int fmt_packet(void *packet, char *buff, size_t n)
{
	memcpy(buff, packet, n);
	return 0;
}

int fmt_work(char *data, char **dict, u_char count)
{
	char *p = strtok(data, ";");
	int i = 0;

	dict = malloc(count * sizeof(char *));

	do {
		dict[i++] = p;
	} while (p = strtok(NULL, ";"));
}
