#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <network/tcpserver/tcpserver.h>
#include <stdbool.h>

extern bool interrupted;

static void tcpserver_accept
(tcpserver_t *server, connectionAcceptedCallback callback)
{
	tcpclient_t *client;
	struct sockaddr_in addr;
	struct epoll_event event;
	socklen_t addrlen = sizeof(addr);
	int fd = accept(server->sockfd, (struct sockaddr *)&addr, &addrlen);

	if (fd == -1)
		return;
	event.data.fd = fd;
	event.events = EPOLLIN;
	if (epoll_ctl(server->epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1)
	{
		close(fd);
		return;
	}
	client = malloc(sizeof(tcpclient_t));
	if (tcpclient_init(client, fd, &addr) == EXIT_FAILURE)
		return;
	linkedlist_append(&server->clients, client);
	if (callback != NULL)
		callback(server->super, client);
}

static void tcpserver_disconnection
(tcpserver_t *server, int sockfd, clientDisconnectedCallback dcallback)
{
	tcpclient_t *client;

	client = tcpserver_find_client(server, sockfd);
	if (client == NULL)
		return;
	linkedlist_remove(&server->clients, client, sizeof(tcpclient_t));
	if (dcallback != NULL)
		dcallback(server->super, client);
	tcpclient_destroy(client);
	free(client);
}

static void tcpserver_receive
(tcpserver_t *server, int sockfd,
messageReceivedCallback mcallback, clientDisconnectedCallback dcallback)
{
	int amount;
	uint8_t *buffer;
	tcpclient_t *client;

	if (ioctl(sockfd, FIONREAD, &amount) == -1)
		return;
	if (amount == 0) {
		tcpserver_disconnection(server, sockfd, dcallback);
		return;
	}
	buffer = malloc(sizeof(uint8_t) * amount);
	if (read(sockfd, buffer, amount) == 0) {
		tcpserver_disconnection(server, sockfd, dcallback);
		return;
	}
	client = tcpserver_find_client(server, sockfd);
	if (client != NULL)
		mcallback(server->super, client, buffer, amount);
	free(buffer);
}

static void tcpserver_handle_epoll_event
(tcpserver_t *server, struct epoll_event *event)
{
	int sockfd = event->data.fd;
	messageReceivedCallback mcallback = server->message_callback;
	clientDisconnectedCallback dcallback = server->disconnect_callback;

	if (sockfd == server->sockfd)
		tcpserver_accept(server, server->accept_callback);
	else
		tcpserver_receive(server, sockfd, mcallback, dcallback);
};

int tcpserver_start
(tcpserver_t *server,
connectionAcceptedCallback accept_callback,
messageReceivedCallback message_callback,
clientDisconnectedCallback disconnect_callback)
{
	if (server == NULL)
		return (EXIT_FAILURE);

	int count = 0;
	struct epoll_event event;
	int epoll_fd = server->epoll_fd;
	struct epoll_event *events = server->epoll_events;

	server->accept_callback = accept_callback;
	server->message_callback = message_callback;
	server->disconnect_callback = disconnect_callback;
	while (server->connected && !interrupted)
	{
		count = epoll_wait(epoll_fd, events, server->capacity, -1);
		for (int index = 0; index < count; index++)
		{
			event = events[index];
			tcpserver_handle_epoll_event(server, &event);
		}
	}
	return (EXIT_SUCCESS);
}
