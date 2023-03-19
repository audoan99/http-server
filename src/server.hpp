/**
 * @file server.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief handle response requersts
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "mime_type.hpp"
#include "lru_cache.hpp"
#include "socket_tcp.hpp"
#include "file_handle.hpp"

#define GET_FILES               "./getfiles"

class Server : public FileHandle, public MimeType, public LRUCache
{
public:
    Server() {}
    ~Server() {}

    /**
     * @brief Send an HTTP response
     * 
     * header:       "HTTP/1.1 404 NOT FOUND" or "HTTP/1.1 200 OK", etc.
     * content_type: "text/plain", etc.
     * body:         the data to send.
     * 
     * @return Return the value from the send() function 
     */
    int send_response(int fd, char *header, char *content_type, void *body, int content_length);

    /**
     * @brief Send a 404 response
     * 
     * @param fd 
     */
    void resp_404(int fd);

    /**
     * @brief Read and return a file from disk or cache
     * 
     * @param fd 
     * @param cache 
     * @param request_path 
     */

    void get_file(int fd, struct cache *cache, char *request_path);

    /**
     * @brief Search for the end of the HTTP header
     * 
     * @param header 
     * @return "Newlines" in HTTP can be (carriage return followed by newline) or
     * (newline) or (carriage return)
     */
    char *find_start_of_body(char *header);

    /**
     * @brief Save data to file
     * 
     * @param body 
     * @return int 
     */
    int post_save(char *body);

    /**
     * @brief Handle HTTP request and send response
     * 
     * @param fd 
     * @param cache 
     */
    void handle_http_request(int fd, struct cache *cache);
private:

};

#endif /* __SERVER_HPP__ */

