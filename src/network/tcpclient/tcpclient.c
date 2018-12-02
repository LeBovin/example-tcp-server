/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <arpa/inet.h>
#include <network/tcpclient/tcpclient.h>

int tcpclient_init
(tcpclient_t *client, int sockfd, struct sockaddr_in *addr)
{
	if (client == NULL || sockfd == -1 || addr == NULL)
		return (EXIT_FAILURE);
	client->sockfd = sockfd;
	client->port = htons(addr->sin_port);
	client->ip = strdup(inet_ntoa(addr->sin_addr));
	client->addr = *addr;
	return (EXIT_SUCCESS);
}

void tcpclient_destroy
(tcpclient_t *client)
{
	if (client == NULL)
		return;
	if (client->sockfd != -1)
		close(client->sockfd);
	if (client->ip != NULL)
		free(client->ip);
	memset(client, 0, sizeof(tcpclient_t));
}

int tcpclient_send
(tcpclient_t *client, const uint8_t *buffer, size_t n)
{
	if (client == NULL || buffer == NULL || n == 0)
		return (EXIT_FAILURE);
	if (write(client->sockfd, buffer, n) != (int)n)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
