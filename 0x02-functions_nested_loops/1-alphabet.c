#include "main.h"
/**
 * main - Entry point
 * Description: print from a to z
 *
 * Return: Always 0 (Success)
 */
void print_alphabet(void)
{
	int i = 97;

	while (i <= 122)
	{
		_putchar(i);
		i++;
	}
	_putchar('\n');
}
