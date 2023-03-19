/**
 * @file mime_type.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief This function support detect type of MIME (Multi-purpose Internet Mail Extensions)
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>
#include <ctype.h>
#include "mime_type.hpp"

char *MimeType::strlower(char *s)
{
    for(char *p = s; *p != '\0'; p++)
    {
        *p = tolower(*p);
    }

    return s;
}

char *MimeType::mime_type_get(char *filename)
{
    char *ext = strrchr(filename, '.');

    if(ext == NULL)
    {
        return DEFAULT_MIME_TYPE;
    }

    ext++;

    strlower(ext);

    if(strcmp(ext, "html") == 0 || strcmp(ext, "htm") == 0) { return (char*)"text/html"; }
    if(strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) { return (char*)"image/jpg"; }
    if(strcmp(ext, "css") == 0) { return (char*)"text/css"; }
    if(strcmp(ext, "js") == 0) { return (char*)"application/javascript"; }
    if(strcmp(ext, "json") == 0) { return (char*)"application/json"; }
    if(strcmp(ext, "txt") == 0) { return (char*)"text/plain"; }
    if(strcmp(ext, "gif") == 0) { return (char*)"image/gif"; }
    if(strcmp(ext, "png") == 0) { return (char*)"image/png"; }

    return DEFAULT_MIME_TYPE;
}