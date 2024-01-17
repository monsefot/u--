#ifndef FILE_H
#define FILE_H

typedef struct {
    char *buffer;
    size_t size;
} File_Content;

File_Content *new_source_code(char *path);

#endif // FILE_H