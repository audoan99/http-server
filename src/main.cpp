/**
 * @file main.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief Main function handles connections and responds to the requests
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "server.hpp"

#define PORT            (char *)"8080"

int main(void)
{
    int newfd;  // listen on sock_fd, new connection on newfd
    struct sockaddr_storage their_addr; // connector's address information
    char s[INET6_ADDRSTRLEN];

    Server l_server;
    SocketTcp l_socket;

    struct cache *cache = l_server.cache_create(10, 0);

    /* Get a listening socket */
    int listenfd = l_socket.get_listener_socket(PORT);

    if (listenfd < 0)
    {
        fprintf(stderr, "webserver: fatal error getting listening socket\n");
        exit(1);
    }

    printf("webserver: waiting for connections on port %s...\n", PORT);

    /*  This is the main loop that accepts incoming connections and
        responds to the request. The main parent process
        then goes back to waiting for new connections. */
    while(1)
    {
        socklen_t sin_size = sizeof their_addr;

        /*  Parent process will block on the accept() call until someone
            makes a new connection: */
        newfd = accept(listenfd, (struct sockaddr *)&their_addr, &sin_size);
        
        if (newfd == -1)
        {
            perror("accept");
            continue;
        }

        // Print out a message that we got the connection
        inet_ntop(their_addr.ss_family, l_socket.get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);
        
        /*  newfd is a new socket descriptor for the new connection.
            listenfd is still listening for new connections. */
        l_server.handle_http_request(newfd, cache);

        close(newfd);
    }

    return 0;
}