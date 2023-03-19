/**
 * @file server.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief handle response requersts
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <mutex>
#include "server.hpp"

std::mutex g_lock;

int Server::send_response(int fd, char *header, char *content_type, void *body, int content_length)
{
    const int max_response_size = 262144; // Default limit in IIS
    char response[max_response_size];
    int response_length;
    time_t t = time(NULL);
    struct tm *local_time = localtime(&t);
    char *timestamp = asctime(local_time);

    response_length = sprintf(response, "%s\nDate %sConnection: close\nContent-Type: %s\nContent-Length: %d\n\n", header, timestamp, content_type, content_length);
    memcpy(response + response_length, body, content_length);
    response_length += content_length + 1;

    /* Send it all! */
    int rv = send(fd, response, response_length, 0);
    if (rv < 0)
    {
        perror("send");
    }

    return rv;
}

void Server::resp_404(int fd)
{
    char filepath[4096];
    struct file_data *filedata;
    char *mime_type;

    /* Fetch the 404.html file */
    snprintf(filepath, sizeof filepath, "%s/404.html", GET_FILES);
    filedata = file_load(filepath);

    if (filedata == NULL)
    {
        fprintf(stderr, "cannot find system 404 file\n");
        exit(3);
    }

    mime_type = mime_type_get(filepath);
    send_response(fd, (char*)"HTTP/1.1 404 NOT FOUND", mime_type, filedata->data, filedata->size);
    file_free(filedata);
}

void Server::get_file(int fd, struct cache *cache, char *request_path)
{
    char filepath[4096];
    struct file_data *filedata;
    char *mime_type;

    if (strcmp(request_path, "/") == 0)
    {
        snprintf(filepath, sizeof filepath, "%s/home_page.html", GET_FILES);
    }
    else
    {
        snprintf(filepath, sizeof filepath, "%s%s", GET_FILES, request_path);
    }

    filedata = file_load(filepath);

    if (filedata == NULL)
    {
        resp_404(fd);
        return;
    }
    else
    {
        mime_type = mime_type_get(filepath);
        cache_put(cache, filepath, mime_type, filedata->data, filedata->size);
        send_response(fd, (char *)"HTTP/1.1 200 OK", mime_type, filedata->data, filedata->size);
    }

    file_free(filedata);
}

char *Server::find_start_of_body(char *header)
{
    header = strtok(header, "\n");
    char *token;
    for (;;)
    {
        token = strtok(NULL, "\n");
        if (token == NULL)
        {
            break;
        }
        if (strcmp(token, "\r") == 0)
        {
            printf("found\n");
            token = strtok(NULL, "\n");
            break;
        }
        printf("token = %s\n", token);
    }

    return token;
}

int Server::post_save(char *body)
{
    g_lock.lock();
    FILE *fp = fopen("./postfiles/posted-file.txt", "a+");
    fputs(body, fp);
    fputs("\n", fp);
    fclose(fp);
    g_lock.unlock();

    return 0;
}

void Server::handle_http_request(int fd, struct cache *cache)
{
    const int request_buffer_size = 65536; // 64KB
    char request[request_buffer_size];

    /* Read request */
    int bytes_recvd = recv(fd, request, request_buffer_size - 1, 0);

    if (bytes_recvd < 0)
    {
        perror("recv");
        return;
    }

    char method[200], path[8192];

    sscanf(request, "%s %s", method, path);

    struct cache_entry *entry = cache_get(cache, path);

    if (entry != NULL)
    {
        send_response(fd, (char *)"HTTP/1.1 200 OK", entry->content_type, entry->content, entry->content_length);
    }
    else
    {

        if (strcmp("GET", method) == 0)
        {
            get_file(fd, cache, path);

        }
        else if (strcmp("POST", method) == 0 && strcmp(path, "/save") == 0)
        {
            char *body = find_start_of_body(request);
            printf("body = %s\n", body);

            int ret = post_save(body);
            if (ret == 0)
            {
                printf("post success\n");
                char *response = (char *)"{\"status\":\"ok\"}";
                send_response(fd, (char *)"HTTP/1.1 201 CREATED", (char *)"application/json", response, strlen(response));
            }
            else
            {
                printf("post failed\n");
            }
        }
        else
        {
            resp_404(fd);
            return;
        }
    }

    free(entry);
}