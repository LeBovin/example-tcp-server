/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <memory.h>
#include <network/tcpserver/tcpserver.h>

static int tcpserver_socket
(tcpserver_t *server, int ip_type, int protocol_type)
{
	server->sockfd = socket(ip_type, protocol_type, 0);
	if (server->sockfd == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int tcpserver_setopt(tcpserver_t *server)
{
	int opt = 1;
	int fd = server->sockfd;
	int flags1 = SOL_SOCKET;
	int flags2 = SO_REUSEADDR | SO_REUSEPORT;

	if (setsockopt(fd, flags1, flags2, &opt, sizeof(opt)) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int tcpserver_bind
(tcpserver_t *server, int ip_type, const char *host, int port)
{
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);

	addr.sin_family = ip_type;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host);
	if (bind(server->sockfd, (struct sockaddr *)&addr, addrlen) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int tcpserver_listen(tcpserver_t *server, size_t capacity)
{
	struct epoll_event evt;
	int e_fd = epoll_create1(0);

	server->epoll_fd = e_fd;
	server->capacity = capacity;
	if (server->epoll_fd == -1)
		return (EXIT_FAILURE);
	server->epoll_events = malloc(sizeof(struct epoll_event) * capacity);
	if (server->epoll_events == NULL)
		return (EXIT_FAILURE);
	if (listen(server->sockfd, capacity) == -1)
		return (EXIT_FAILURE);
	evt.events = EPOLLIN;
	evt.data.fd = server->sockfd;
	if (epoll_ctl(e_fd, EPOLL_CTL_ADD, server->sockfd, &evt) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int tcpserver_init
(tcpserver_t *server, void *super, tcpserver_informations_t *informations)
{
	int ip_t = informations->ip_type;
	int proto_t = informations->protocol_type;
	size_t capacity = informations->capacity;
	const char *host = informations->host;
	int port = informations->port;

	if (linkedlist_init(&server->clients) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (tcpserver_socket(server, ip_t, proto_t) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (tcpserver_setopt(server) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (tcpserver_bind(server, ip_t, host, port) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (tcpserver_listen(server, capacity) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	server->super = super;
	server->connected = 1;
	return (EXIT_SUCCESS);
}