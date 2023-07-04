#include "main.h"

/**
 * _strlen - return the length of a string
 *
 * @s: string parameter input
 *
 * Return: length if a string
 */

int _strlen(char *s)
{
	int counter;

	for (counter = 0; *s != '\0'; s++)
	{
		++counter;
	}
	return (counter);
}
