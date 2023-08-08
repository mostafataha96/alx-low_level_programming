#include "custom_io.h"
#include <stdio.h>
#include <stdlib.h>

char *allocate_memory_for_buffer(char *filename);
void close_custom_file(int descriptor);

/**
 * allocate_memory_for_buffer - Allocates memory for a buffer of size 1024 bytes.
 * @filename: The name of the file for which the buffer is allocated.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *allocate_memory_for_buffer(char *filename)
{
    char *custom_buffer;

    custom_buffer = malloc(sizeof(char) * 1024);

    if (custom_buffer == NULL)
    {
        custom_dprintf(CUSTOM_STDERR_FILENO,
                       "Error: Unable to allocate memory for %s\n", filename);
        exit(EXIT_FAILURE);
    }

    return (custom_buffer);
}

/**
 * close_custom_file - Closes custom file descriptors.
 * @descriptor: The custom file descriptor to be closed.
 */
void close_custom_file(int descriptor)
{
    int close_status;

    close_status = custom_close(descriptor);

    if (close_status == -1)
    {
        custom_dprintf(CUSTOM_STDERR_FILENO,
                       "Error: Unable to close descriptor %d\n", descriptor);
        exit(EXIT_FAILURE);
    }
}

/**
 * main - Copies the contents of one custom file to another.
 * @argc: The number of arguments provided to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on successful execution.
 *
 * Description: Exits with different codes for various error scenarios:
 * 97 - Incorrect argument count.
 * 98 - Inaccessible source file.
 * 99 - Unable to create or write to the destination file.
 * 100 - Failure in closing source or destination file.
 */
int main(int argc, char *argv[])
{
    int source_file, destination_file, read_status, write_status;
    char *custom_buffer;

    if (argc != 3)
    {
        custom_dprintf(CUSTOM_STDERR_FILENO, "Usage: custom_cp source_file destination_file\n");
        exit(97);
    }

    custom_buffer = allocate_memory_for_buffer(argv[2]);
    source_file = custom_open(argv[1], CUSTOM_O_RDONLY);
    read_status = custom_read(source_file, custom_buffer, 1024);
    destination_file = custom_open(argv[2], CUSTOM_O_CREAT | CUSTOM_O_WRONLY | CUSTOM_O_TRUNC, 0664);

    do
    {
        if (source_file == -1 || read_status == -1)
        {
            custom_dprintf(CUSTOM_STDERR_FILENO,
                           "Error: Unable to read from source file %s\n", argv[1]);
            free(custom_buffer);
            exit(98);
        }

        write_status = custom_write(destination_file, custom_buffer, read_status);
        if (destination_file == -1 || write_status == -1)
        {
            custom_dprintf(CUSTOM_STDERR_FILENO,
                           "Error: Unable to write to destination file %s\n", argv[2]);
            free(custom_buffer);
            exit(99);
        }

        read_status = custom_read(source_file, custom_buffer, 1024);
        destination_file = custom_open(argv[2], CUSTOM_O_WRONLY | CUSTOM_O_APPEND);

    } while (read_status > 0);

    free(custom_buffer);
    close_custom_file(source_file);
    close_custom_file(destination_file);

    return (EXIT_SUCCESS);
}

