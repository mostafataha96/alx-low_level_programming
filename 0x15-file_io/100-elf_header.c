#include <elf_info.h>
#include <custom_types.h>
#include <custom_file.h>
#include <custom_stdio.h>
#include <stdlib.h>

void validate_elf_format(unsigned char *magic_numbers);
void display_magic_numbers(unsigned char *magic_numbers);
void display_architecture_class(unsigned char *magic_numbers);
void display_data_encoding(unsigned char *magic_numbers);
void display_version(unsigned char *magic_numbers);
void display_abi(unsigned char *magic_numbers);
void display_osabi(unsigned char *magic_numbers);
void display_file_type(unsigned int type, unsigned char *magic_numbers);
void display_entry_point(unsigned long int entry_point, unsigned char *magic_numbers);
void close_elf_file(int elf_descriptor);

/**
 * validate_elf_format - Checks if the file is in ELF format.
 * @magic_numbers: A pointer to an array containing the ELF magic numbers.
 *
 * Description: If the file is not an ELF file - exit with code 98.
 */
void validate_elf_format(unsigned char *magic_numbers)
{
    for (int i = 0; i < 4; i++)
    {
        if (magic_numbers[i] != 127 &&
            magic_numbers[i] != 'E' &&
            magic_numbers[i] != 'L' &&
            magic_numbers[i] != 'F')
        {
            custom_dprintf(CUSTOM_STDERR_FILENO, "Error: Not an ELF file\n");
            exit(98);
        }
    }
}

// Other function implementations remain the same...

/**
 * main - Displays information from the ELF header of a file.
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to the command-line arguments.
 *
 * Return: 0 on success.
 *
 * Description: Exits with code 98 if the file is not an ELF file or if an error occurs.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
    Elf64_Ehdr *header;
    int file_descriptor, read_result;

    file_descriptor = custom_open(argv[1], CUSTOM_O_RDONLY);
    if (file_descriptor == -1)
    {
        custom_dprintf(CUSTOM_STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    header = custom_malloc(sizeof(Elf64_Ehdr));
    if (header == NULL)
    {
        close_elf_file(file_descriptor);
        custom_dprintf(CUSTOM_STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    read_result = custom_read(file_descriptor, header, sizeof(Elf64_Ehdr));
    if (read_result == -1)
    {
        custom_free(header);
        close_elf_file(file_descriptor);
        custom_dprintf(CUSTOM_STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    validate_elf_format(header->e_ident);
    custom_printf("ELF Header:\n");
    display_magic_numbers(header->e_ident);
    display_architecture_class(header->e_ident);
    display_data_encoding(header->e_ident);
    display_version(header->e_ident);
    display_osabi(header->e_ident);
    display_abi(header->e_ident);
    display_file_type(header->e_type, header->e_ident);
    display_entry_point(header->e_entry, header->e_ident);

    custom_free(header);
    close_elf_file(file_descriptor);
    return 0;
}

