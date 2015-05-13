#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>


#define PORT "1025"

/*
 * This file implements net operations
 * 
 * TODO:
 * 	- Consider return values
 * 	- Make a net header file
 * 	- debug
 */


size_t raw_send(const char *addr, const char *port, const char *data, int flags)
/* TODO:
	- implement arg 'flags'
*/
{
	int sockd, retval;
	struct addrinfo *addr_s;

	getaddrinfo(addr, port, 0, &addr_s);

	sockd = socket(AF_INET, SOCK_STREAM, 0);

	retval = connect(sockd, addr_s->ai_addr, addr_s->ai_addrlen);

	// TODO: some comparations for 'retval'

	retval = send(sockd, data, sizeof(data), 0);

	return (size_t)retval;
}

int raw_recv(char *buf, size_t buf_len)
{
	struct addrinfo *addr_s, hints;
	struct sockaddr_storage p_addr;
	socklen_t addr_len;
	int sockd, peerd, retval, y=1;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &addr_s);
	sockd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

	retval = bind(sockd, addr_s->ai_addr, addr_s->ai_addrlen);
	if(retval == -1) 
		return -1;


	listen(sockd, 5); /* TODO: config max inc connections */

	addr_len = sizeof(p_addr);
	peerd = accept(sockd, (struct sockaddr *)&p_addr, &addr_len);

	retval = recv(peerd, buf, buf_len, 0);

	close(peerd);

	return retval;
}
