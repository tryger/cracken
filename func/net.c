#include <sys/types.h> //
#include <sys/socket.h> 
#include <netdb.h> //
#include <stdlib.h> //
#include <string.h> //
#include <netinet/in.h>
#include <pthread.h>

#define PORT "7070"

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

int raw_listen(void *(*handler)())
{
	struct addrinfo *addr_s, hints;
	struct sockaddr_storage p_addr;
	socklen_t addr_size;
	int sockd, peerd, retval, y=1;
	pthread_t tid;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &addr_s);

	
	if ((sockd = socket(addr_s->ai_family, addr_s->ai_socktype, addr_s->ai_protocol)) < 0) {
		perror("socket()");
		return -1;
}
	setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));

	if (bind(sockd, addr_s->ai_addr, addr_s->ai_addrlen) < 0) {
		perror("bind()");
		return -1;
	}

	listen(sockd, 5); /* TODO: config max inc connections */

	addr_size = sizeof(struct sockaddr_storage);
	
	while ((peerd = accept(sockd, (struct sockaddr *)&p_addr, &addr_size)) >= 0) {
		if(pthread_create(&tid, NULL, handler, (void *)&peerd) < 0)
			return -1;
	}
	
	perror("accept()");
	return 0;
}

int raw_close(int sockd)
{
	return close(sockd);
}	
