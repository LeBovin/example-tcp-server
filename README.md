# simple-generic-tcp-server

With this example you can:
* Run in few seconds a TCP server
* Overload this TCP server (ex: build an IRC server, FTP server, game server, ...)

# The basic usage:
```
#include <signal.h>
#include <stdbool.h>
#include <network/tcpserver/tcpserver.h>
#include <stdio.h>

/*
 * Need to be declared to stop the server when signal is catched
 */
bool interrupted = false;

void signal_handler(int signum)
{
    (void)signum;
    interrupted = true;
}

void accept_callback(void *super, tcpclient_t *client)
{
    printf("incoming connection from: %s:%d\n", client->ip, client->port);
}

void receive_callback(void *super, tcpclient_t *client, const uint8_t *buffer, size_t size)
{
    printf("(%s:%d) message received: %s\n", client->ip, client->port, buffer);
}

void disconnect_callback(void *super, tcpclient_t *client)
{
    printf("%s:%d disconnected.\n", client->ip, client->port);
}

int main(int ac, char **argv)
{
    /*
     * Catch signals
     * call the signal_handler function to interrupt the server
     */
    signal(SIGINT, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGTERM, signal_handler);

    /*
     * Configure the tcp server
     * capacity = maximum of simultaneous connection
     * host = host to run the server
     * port = port to run the server
     * ip_type = IPv4 (AF_INET) or IPv6 (AF_INET6)
     * protocol_type = TCP (SOCK_STREAM), UDP (SOCK_DGRAM) or other
     */
    tcpserver_informations_t server_configuration;
    server_configuration.capacity = 100;
    server_configuration.host = "127.0.0.1";
    server_configuration.port = 6666;
    server_configuration.ip_type = AF_INET;
    server_configuration.protocol_type = SOCK_STREAM;


    /*
     * We first declare a tcpserver_t structure
     */
    tcpserver_t server;

    /*
     * Then we initialize the server with previous configuration
     * The super argument isn't use in this example
     */
    tcpserver_init(&server, NULL, &server_configuration);

    /*
     * Then we start the server and give callback functions
     * WARNING: this call block the current thread
     */
    tcpserver_start(&server, accept_callback, receive_callback, disconnect_callback);

    /*
     * We do not forget to destroy the tcpserver
     * Obviously, this release of the ressources allocated
     */
    tcpserver_destroy(&server);
}
```
