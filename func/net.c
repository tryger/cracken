#include <sys/types.h> //
#include <sys/socket.h> 
#include <netdb.h> //
#include <stdlib.h> //
#include <string.h> //
#include <netinet/in.h>


#define PORT 7070

/*
 * This file implements net operations
 * 
 * TODO:
 * 	- Consider return values
 * 	- Make a net header file
 * 	- debug
 */


int raw_connect(const char *addr, unsigned short port /*const char *port*/)
/* TODO:
	- implement arg 'flags'
*/
{

	int sockd, retval;
	struct sockaddr_in servaddr;


	sockd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(addr);
	servaddr.sin_port = htons(port);

	retval = connect(sockd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	return sockd;

	//send(sockd, data, count, 0);

	//close(sockd);
	//n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);

/*
	int sockd, retval;
	struct addrinfo *addr_s;

	getaddrinfo(addr, port, 0, &addr_s);

	sockd = socket(AF_INET, SOCK_STREAM, 0);

	retval = connect(sockd, addr_s->ai_addr, addr_s->ai_addrlen);

	// TODO: some comparations for 'retval'

	retval = send(sockd, data, strlen(data), 0);

	close(sockd);

	return (size_t)retval;
*/
}

size_t raw_send(int sockd, char *data, size_t n)
{
	return send(sockd, data, n, 0);
}

size_t raw_recv(int sockd, char *buf, size_t n)
{
	return recv(sockd, buf, n, 0);
}

int raw_listen(char *buf, size_t buf_len)
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

int raw_close(int sockd)
{
	return close(sockd);
}
