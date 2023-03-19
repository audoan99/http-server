/**
 * @file mime_type.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief This function support detect type of MIME (Multi-purpose Internet Mail Extensions)
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MIME_TYPE_HPP__
#define __MIME_TYPE_HPP__

#define DEFAULT_MIME_TYPE           (char*)"application/octet-stream"

class MimeType
{
public:
    MimeType() {}
    ~MimeType() {}

    /**
     * @brief Lowercase a string
     *
     * @param s
     * @return char*
     */
    char *strlower(char *s);

    /**
     * @brief Return a MIME type for a given filename
     *
     * @param filename
     * @return char*
     */
    char *mime_type_get(char *filename);

private:

};

#endif /* __MIME_TYPE_HPP__ */