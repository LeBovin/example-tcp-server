//
// Created by flaviangontier on 12/3/18.
//

#ifndef SIMPLE_GENERIC_TCP_SERVER_OVERLOAD_SERVER_H
#define SIMPLE_GENERIC_TCP_SERVER_OVERLOAD_SERVER_H

#include <linkedlist/linkedlist.h>
#include <network/tcpserver/tcpserver.h>

struct overload_server_s
{
    tcpserver_t server;
    linkedlist_t overload_clients;
};
typedef struct overload_server_s overload_server_t;

int overload_server_init(overload_server_t *server);
int overload_server_start(overload_server_t *server);
int overload_server_destroy(overload_server_t *server);

#endif //SIMPLE_GENERIC_TCP_SERVER_OVERLOAD_SERVER_H
