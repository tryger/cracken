#include <stdlib.h>

#include "packet.h"
#include "net.h"

int _registered = 0;

/* char *prnt can be implemented with global val from config file */

int register_me(char *prnt, char nodetype)
{
	int sockd;

	struct hi_packet p = {
		.op = OP_HI,
		.hi_op = HI_REGME,
		.node_type = nodetype
	};

	sockd = raw_connect(prnt, 7070);
	if(sockd < 0)
		return -1;

	if(send_hi_packet(sockd, &p) != HI_LEN)
		return -1;

	if(recv_hi_packet(sockd, &p) != HI_LEN)
		return -1;

	raw_close(sockd);

	if(p.hi_op == HI_REGOK) {
		_registered = 1;
		return 0;
	} else {
		_registered = 0;
		return -1;
	}
}

int getwork(char *prnt, u_short count, char **dict)
{
	int sockd;

	struct getw_packet p = {
		.op = OP_GETW,
		.getw_op = GETW_RQST,
		.count = count,
		.length = 0
	};

	sockd = raw_connect(prnt, 7070);
	if(sockd < 0)
		return -1;

	if(send_getw_packet(sockd, &p) != GETW_LEN)
		return -1;

	if(recv_getw_packet(sockd, &p, dict) != GETW_LEN)
		return -1;

	if(send_getw_packet(sockd, &p) != GETW_LEN)
		return -1;

	raw_close(sockd);
}