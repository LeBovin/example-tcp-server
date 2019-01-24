//
// Created by flaviangontier on 12/3/18.
//

#include <stdio.h>
#include "overload_server.h"
#include "overload_client.h"

static void on_message_received(overload_server_t *server, tcpclient_t *client, uint8_t *message, size_t size)
{
}

static void on_client_connected(overload_server_t *server, tcpclient_t *client)
{
    overload_client_t *overload_client = malloc(sizeof(overload_client_t));
    if (overload_client == NULL)
    {
        fprintf(stderr, "[on_client_connected] client memory allocation failed.");
        return;
    }

    overload_client->client = client;

    int err = linkedlist_append(&server->overload_clients);
    if (err)
    {
        free(overload_client);
        fprintf(stderr, "[on_client_connected] error when appending client");
    }
}

static void on_client_disconnected(overload_server_t *server, tcpclient_t *client)
{
}

int overload_server_init(overload_server_t *server)
{
    int err = 0;

    err = tcpserver_init(&server->server);
    if (err)
        return (EXIT_FAILURE);

    err = linkedlist_init(&server->overload_clients);
    if (err)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

int overload_server_start(overload_server_t *server)
{
    /*
     * WARNING: as mentioned on the basic example, tcpserver_start blocks the current thread
     */
    int err = tcpserver_start(on_client_connected, on_message_received, on_client_disconnected);
    if (err)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}

int overload_server_destroy(overload_server_t *server)
{
    linkedlist_destroy(&server->overload_clients);
    tcpserver_destroy(&server->server);

    return (EXIT_SUCCESS);
}
