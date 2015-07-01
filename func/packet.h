#define NODETYPE_ROOT 0x00
#define NODETYPE_SPLT 0x01
#define NODETYPE_USER 0x02


#define OP_HI 0x00
#define OP_GETW 0x01

struct packet {
	int from;
	int to;

	char opcode;
	char data[];
}

#define HI_REGME 0x00
#define HI_REGOK 0x01

struct hi_packet {
	char op;
	char node_type;
}

#define GETW_DEFAULT_LEN 4000

#define GETW_OP_RQST 0x00
#define GETW_OP_RSPS 0x01

struct getw_packet {
	char op;
	int len;
	char data[];
}
