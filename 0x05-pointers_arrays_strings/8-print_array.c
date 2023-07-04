#include <main.h>

/**
 * print_array -rints n elements of an array of integer
 *
 * @n: elements parameter input
 * @a: string parameter input
 * return: nothing
 */

void print_array(int *a, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (i != (n - 1))
			printf("%d, ", a[i]);
		else
			printf("%d", a[i]);
	}
	printf("\n");
}
