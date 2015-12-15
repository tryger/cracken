#include <stdlib.h>
#include <stdio.h>

#include "packet.h"
#include "net.h"

extern FILE *dictp;
extern char *prnt;
extern char *hash;

int _registered = 0;

/* char *prnt can be implemented with global val from config file */

/***************
 * SERVER CODE */
int get_packet(int sockd)
{
	char buf[MAX_PACKET_LEN];

	raw_recv(sockd, &buf, MAX_PACKET_LEN);

	switch(buf[0]) {
		case OP_HASH:
			hash_packet(sockd, &buf);
			break;
		case OP_GETW:
			getw_packet(sockd, &buf);
			break;
	}

	raw_close(sockd);
}

int getw_packet(int sockd, char *buf)
{
	struct getw_packet *p = (struct getw_packet *)malloc(GETW_LEN);

	fmt_packet(buf, p, GETW_LEN);

	switch(p->getw_op) {
		case GETW_RQST:
			offer_work(sockd, p);
			break;
	}

	free(p);
}

int offer_work(int sockd, struct getw_packet *p)
{
	char *data = malloc(0);

	p->length = get_n_pass(dictp, &data, p->count);

	send_getw_packet(sockd, p, data);
	
	free(data);

	recv_getw_packet(sockd, p, NULL);
}




int hash_packet(int sockd, char *buf)
{
	struct hash_packet *p = (struct hash_packet *)malloc(HASH_LEN);

	fmt_packet(buf, p, HASH_LEN);

	buf += HASH_LEN;


	switch(p->hash_op) {
		case HASH_RQST:
			offer_hash(sockd, p);
			break;
		case HASH_DONE:
			hash_broken(sockd, p, buf);
			break;
	}

	free(p);
}

int offer_hash(int sockd, struct hash_packet *p)
{
	char buf[HASH_LEN];

	p->hash_op = HASH_OFFR;
	p->algorithm = HASH_MD5;
	p->id = 0;
	p->hash_len = 32;
	p->plain_len = 0;

	send_hash_packet(sockd, p, hash, NULL);

	recv_hash_packet(sockd, p, NULL, NULL);

	if (*(buf+1) == HASH_ACPT)
		return 0;
	return -1;
}

int hash_broken(int sockd, struct hash_packet *p, char *buf)
{
	char ha[p->hash_len + 1];
	char pl[p->plain_len + 1];

	memcpy(&ha, buf, p->hash_len);
	ha[p->hash_len] = '\x00';
	memcpy(&pl, buf + p->hash_len, p->plain_len);
	pl[p->plain_len] = '\x00';

	printf("\nHASH BROKEN!!\n");
	printf("%s\t%s\n", &ha, &pl);

	
	// broadcast winwin

	exit(0);
}

/***************
 * CLIENT CODE */
  
int registerme(/*int sockd, */char nodetype)
{
	int sockd = raw_connect(prnt, 7070);

	struct hi_packet p = {
		.op = OP_HI,
		.hi_op = HI_REGME,
		.node_type = nodetype
	};

	//sockd = raw_connect(prnt, 7070);
	if(sockd < 0)
		return -1;

	if(send_hi_packet(sockd, &p) != HI_LEN)
		return -1;

	if(recv_hi_packet(sockd, &p) != HI_LEN)
		return -1;

	//raw_close(sockd);

	if(p.hi_op == HI_REGOK) {
		_registered = 1;
		return 0;
	} else {
		_registered = 0;
		return -1;
	}

	raw_close(sockd);
}

int gethash(/*int sockd,*/ char **hash)
{
	int sockd = raw_connect(prnt, 7070);

	struct hash_packet p = {
		.op = OP_HASH,
		.hash_op = HASH_RQST,
		.algorithm = 0,
		.id = 0,
		.hash_len = 0,
		.plain_len = 0
	};

	send_hash_packet(sockd, &p, NULL, 0, NULL, 0);

	recv_hash_packet(sockd, &p, hash, NULL);

	p.hash_op = HASH_ACPT;
	p.hash_len = 0;

	send_hash_packet(sockd, &p, NULL, 0, NULL, 0);

	raw_close(sockd);
}

int solved(/*int sockd, */char *hash, char *plain)
{
	int sockd = raw_connect(prnt, 7070);

	int hlen = strlen(hash);
	int plen = strlen(plain);

	struct hash_packet p = {
		.op = OP_HASH,
		.hash_op = HASH_DONE,
		.algorithm = 0,
		.id = 0,
		.hash_len = hlen,
		.plain_len = plen
	};


	send_hash_packet(sockd, &p, hash, plain);

	raw_close(sockd);
}

u_short getwork(/*int sockd, */u_short count, char **dict)
{
	int sockd = raw_connect(prnt, 7070);

	struct getw_packet p = {
		.op = OP_GETW,
		.getw_op = GETW_RQST,
		.count = count,
		.length = 0
	};


	//sockd = raw_connect(prnt, 7070);
	if(sockd < 0)
		return -1;

	send_getw_packet(sockd, &p);

	recv_getw_packet(sockd, &p, dict);

	p.getw_op = GETW_ACPT;

	//send_getw_packet(sockd, &p, NULL); 

	raw_close(sockd);

	return p.count;
}
