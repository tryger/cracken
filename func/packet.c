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



int send_hash_packet(int sockd, struct hash_packet *packet, char *hash, u_short hlen, char *plain, u_short plen)
{
	int len = hlen + plen;

	char rawp[HASH_LEN + len];

	if(fmt_packet(packet, &rawp, HASH_LEN))
		return ERR_MALFORMEDPKT;

	if(hash != NULL)
		memcpy((&rawp) + HASH_LEN, hash, hlen);
	if(plain != NULL)
		memcpy((&rawp) + HASH_LEN + hlen, plain, plen);


	return raw_send(sockd, &rawp, HASH_LEN + len);
}
int recv_hash_packet(int sockd, struct hash_packet *packet, char **hash, char **plain)
{
	char *data = malloc(HASH_LEN);
	int len;

	raw_recv(sockd, data, HASH_LEN);
	fmt_packet(data, packet, HASH_LEN);

	len = packet->hash_len + packet->plain_len;

	data = realloc(data, len);

	raw_recv(sockd, data, len);

	*hash = malloc(packet->hash_len + 1);
	if(plain != NULL)
		*plain = malloc(packet->plain_len + 1);

	memcpy(*hash, data, packet->hash_len);
	if(plain != NULL)
		memcpy(*hash, data + packet->hash_len, packet->plain_len);

	*(hash + packet->hash_len) = 0;
	if(plain != NULL)
		*(plain + packet->plain_len) = 0;

	free(data);
	//Free hash and plain somewhere in the future
}



int send_getw_packet(int sockd, struct getw_packet *packet)
{
	char rawp[GETW_LEN];

	if(fmt_packet(packet, &rawp, GETW_LEN))
		return ERR_MALFORMEDPKT;

	return raw_send(sockd, &rawp, HI_LEN);
}
int recv_getw_packet(int sockd, struct getw_packet *packet, char **dict)
{
	char *data = malloc(GETW_LEN);

	raw_recv(sockd, data, GETW_LEN);
	fmt_packet(data, packet, GETW_LEN);

	data = realloc(data, packet->length);

	raw_recv(sockd, data, packet->length);
	fmt_work(data, dict, packet->count);

	//free(data);
	//Not necessary, **dict pointing to it. Free it with dict
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

	do {
		dict[i++] = p;
	} while (p = strtok(NULL, ";"));

	return dict;
}
