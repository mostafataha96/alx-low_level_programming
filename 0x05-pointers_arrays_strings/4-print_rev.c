#include <main.h>

/**
 * print_rev - prints reversed string, followed by a new line
 * @a: pointer to the string to print
 * return: void
 */

void print_rev(char *s)
{
	int i = 0;

	while (s[i])
		i++;

	while (i--)
	{
		_putchar([i]);
	}
	_putchar('\n');
}
