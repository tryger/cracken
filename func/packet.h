#include <sys/types.h>


/* NODE TYPES */
#define NODETYPE_ROOT 0x00
#define NODETYPE_SPLT 0x01
#define NODETYPE_USER 0x02

/* OPCODES */
#define OP_HI 0x00
#define OP_GETW 0x01

/* PACKET LENGTHS */
#define HI_LEN 2
#define GETW_LEN 4


/* HI packet */
#define HI_REGME 0x00
#define HI_REGOK 0x01

struct hi_packet {
	u_char op;
	u_char node_type;
}

/* GETW packet */
#define WORK_DEFAULT_LEN 400  /* ??? */

#define GETW_OP_REQUEST 0x00
#define GETW_OP_OFFER 0x01
#define GETW_OP_ACCEPT 0x02

struct getw_packet {
	u_char op;
	u_short len;
	char data[];
}



/* ERROR CODES */
#define ERR_MALFORMEDPKT 1
