/**
 * @file file.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief Handle read file
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file_handle.hpp"

struct file_data *FileHandle::file_load(char *filename)
{
    char *buffer, *p;
    struct stat buf;
    int bytes_read, bytes_remaining, total_bytes = 0;

    /* Get the file size */
    if (stat(filename, &buf) == -1)
    {
        return NULL;
    }

    /* Make sure it's a regular file */
    if (!(buf.st_mode & S_IFREG))
    {
        return NULL;
    }

    /* Open the file for reading */
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return NULL;
    }

    /* Allocate that many bytes */
    bytes_remaining = buf.st_size;

    p = buffer = (char *)malloc(bytes_remaining);
    if (buffer == NULL)
    {
        return NULL;
    }

    /* Read in the entire file */
    while (bytes_read = fread(p, 1, bytes_remaining, fp), bytes_read != 0 && bytes_remaining > 0)
    {
        if (bytes_read == -1)
        {
            free(buffer);
            return NULL;
        }

        bytes_remaining -= bytes_read;
        p += bytes_read;
        total_bytes += bytes_read;
    }

    /* Allocate the file data struct */
    struct file_data *filedata = (struct file_data *)malloc(sizeof *filedata);
    if (filedata == NULL)
    {
        free(buffer);
        return NULL;
    }

    filedata->data = buffer;
    filedata->size = total_bytes;

    return filedata;
}

void FileHandle::file_free(struct file_data *filedata)
{
    free(filedata->data);
    free(filedata);
}
