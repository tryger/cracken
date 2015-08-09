#include "../func/packet.h"

int main()
{
	struct hi_packet p = {
		.op = HI_REGME,
		.node_type = NODETYPE_USER
	};

	send_packet("192.168.1.142", &p);

	return 0;
}
