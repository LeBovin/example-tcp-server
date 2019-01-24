cmake_minimum_required(VERSION 3.11)
project(simple_generic_tcp_server C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)
include_directories(inc/concurrency)
include_directories(inc/linkedlist)
include_directories(inc/network)
include_directories(inc/network/tcpclient)
include_directories(inc/network/tcpserver)

add_executable(simple_generic_tcp_server
        examples/basic/main.c
        inc/linkedlist/linkedlist.h
        inc/network/tcpclient/tcpclient.h
        inc/network/tcpserver/tcpserver.h
        src/linkedlist/add.c
        src/linkedlist/destroy.c
        src/linkedlist/init.c
        src/linkedlist/insert.c
        src/linkedlist/remove.c
        src/linkedlist/stack.c
        src/linkedlist/utils.c
        src/network/tcpclient/tcpclient.c
        src/network/tcpserver/destroy.c
        src/network/tcpserver/init.c
        src/network/tcpserver/send.c
        src/network/tcpserver/start.c
        src/network/tcpserver/utils.c examples/overload/overload.c examples/overload/overload_server.h examples/overload/overload_client.h examples/overload/overload_server.c)
