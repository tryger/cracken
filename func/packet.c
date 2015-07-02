#include "packet.h"

int send_packet(char *dst, char op, void *packet)
{
	switch(*packet) {
		case OP_HI:
			send_hi_packet(dst, (struct hi_packet *) packet);
			break;
		case OP_GETW:
			send_getw_packet(dst, (struct getw_packet *) packet);
			break;
	}
}

int send_hi_packet(char *dst, struct hi_packet *packet)
{
	char data[HI_LEN];

	if(fmt_hi_packet(hi_packet, data) != 0)
		return ERR_MALFORMEDPKT;

	
	
}

int fmt_hi_packet(struct hi_packet *packet, char buff[])
{
	
}

int send_getw_packet(char *dst, struct *hi_packet)
{
	char data[GETW_LEN];
}
