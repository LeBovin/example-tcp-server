#ifndef PSU_MYIRC_2017_TCPSERVER_H
#define PSU_MYIRC_2017_TCPSERVER_H

#include <stdint.h>
#include <netinet/in.h>
#include <linkedlist.h>
#include <tcpclient.h>

typedef void(*connectionAcceptedCallback)
(void *super, tcpclient_t *client);
typedef void(*messageReceivedCallback)
(void *super, tcpclient_t *client, const uint8_t *buffer, size_t);
typedef void(*clientDisconnectedCallback)
(void *super, tcpclient_t *client);

struct tcpserver_informations_s
{
	int port;
	int ip_type;
	const char *host;
	int protocol_type;
	size_t capacity;
};
typedef struct tcpserver_informations_s tcpserver_informations_t;


struct tcpserver_s
{
	int sockfd;
	linkedlist_t clients;
	struct sockaddr_in addr;
	int epoll_fd;
	struct epoll_event *epoll_events;
	void *super;
	int connected;
	size_t capacity;
	messageReceivedCallback message_callback;
	connectionAcceptedCallback accept_callback;
	clientDisconnectedCallback disconnect_callback;
};
typedef struct tcpserver_s tcpserver_t;

int tcpserver_init
(tcpserver_t *server, void *super, tcpserver_informations_t *informations);
void tcpserver_destroy
(tcpserver_t *server);
int tcpserver_start
(tcpserver_t *server,
connectionAcceptedCallback accept_callback,
messageReceivedCallback message_callback,
clientDisconnectedCallback disconnect_callback);

void tcpserver_sendAll
(tcpserver_t *server, const uint8_t *buffer, size_t n);
tcpclient_t *tcpserver_find_client
(tcpserver_t *server, int fd);

#endif //PSU_MYIRC_2017_TCPSERVER_H
