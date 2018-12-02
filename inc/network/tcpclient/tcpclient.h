/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#ifndef PSU_MYIRC_2017_TCPCLIENT_H
#define PSU_MYIRC_2017_TCPCLIENT_H

#include <netinet/in.h>

struct tcpclient_s
{
	char *ip;
	int port;
	int sockfd;
	struct sockaddr_in addr;
};
typedef struct tcpclient_s tcpclient_t;

int tcpclient_init
(tcpclient_t *client, int sockfd, struct sockaddr_in *addr);
int tcpclient_send
(tcpclient_t *client, const uint8_t *buffer, size_t n);
void tcpclient_destroy
(tcpclient_t *client);

#endif //PSU_MYIRC_2017_TCPCLIENT_H
