#include <sys/types.h>

/* NODE TYPES */
#define NODETYPE_ROOT 0x00
#define NODETYPE_SPLT 0x01
#define NODETYPE_USER 0x02

/* OPCODES */
#define OP_HI 0x01
#define OP_GETW 0x02
#define OP_DONEW 0x03

/* PACKET LENGTHS */
#define HI_LEN sizeof(struct hi_packet)
#define GETW_LEN sizeof(struct getw_packet)


/* HI packet */
#define HI_REGME 0x01
#define HI_REGOK 0x02
#define HI_REGFLT 0x03
#define HI_RESET 0x04

struct hi_packet {
	u_char op;
	u_char hi_op;
	u_char node_type;
};

/* GETW packet */
#define WORK_DEFAULT_COUNT 400  /* ??? */

#define GETW_RQST 0x01
#define GETW_OFFR 0x02
#define GETW_ACPT 0x03
#define GETW_DROP 0x04
#define GETW_DONE 0x05
#define GETW_ERRO 0x06

struct getw_packet {
	u_char op;
	u_char getw_op;
	u_short count;
	u_long length;
};



/* ERROR CODES */
#define ERR_MALFORMEDPKT 1
