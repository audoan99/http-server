/**
 * @file socket_tcp.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief This function support handling connection via TCP/IP socket
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __SOCKET_TCP_HPP__
#define __SOCKET_TCP_HPP__

#include <netdb.h>
#include <arpa/inet.h>

#define BACKLOG                 10	 //How many pending connections queue will hold

class SocketTcp
{
public:
    SocketTcp() {}
    ~SocketTcp() {}

    /**
     * @brief Gets an Internet address, either IPv4 or IPv6
     *
     * @param sa
     * @note Helper function to make printing easier
     */

    void *get_in_addr(struct sockaddr *sa);
    /**
     * @brief Return the main listening socket
     *
     * @param port
     * @return -1 or error
     */
    int get_listener_socket(char *port);
private:

};

#endif /* __SOCKET_TCP_HPP__ */