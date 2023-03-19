/**
 * @file file.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief Handle read file
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __FILE_HPP__
#define __FILE_HPP__

struct file_data
{
    int size;
    void *data;
};

class FileHandle
{
public:
    FileHandle() {}
    ~FileHandle() {}

    /**
     * @brief Loads a file into memory and returns a pointer to the data
     *
     * @param filename
     * @return struct file_data*
     * @note Buffer is not NUL-terminated
     */
    struct file_data *file_load(char *filename);

    /**
     * @brief Frees memory allocated by file_load()
     *
     * @param filedata
     */
    void file_free(struct file_data *filedata);
private:

};

#endif /* __FILE_HPP__ */
