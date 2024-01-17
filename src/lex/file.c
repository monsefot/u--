#include <stdio.h>
#include <stdlib.h>

#include "./file.h"

File_Content *new_source_code(char *path) {
    FILE *file = fopen(path, "r");
	if (!file)
	{
		fprintf(stderr, "[EROOR] No such file found: %s\n", path);
		return NULL;
	}

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);

    // Check if memory allocation was successful
    if (buffer == NULL) {
        perror("[ERROR] Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read the file content into the buffer
    size_t read_size = fread(buffer, 1, file_size, file);

    // Check if the read operation was successful
    if (read_size != file_size) {
        fprintf(stderr, "[ERROR] Couldn't read the file: %s\n", path);
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[file_size] = '\0';

    fclose(file);

    File_Content *content = (File_Content *)malloc(sizeof(File_Content));
    content->buffer = buffer;
    content->size = file_size;
    return content;
}