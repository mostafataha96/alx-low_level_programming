#include "main.h"
/**
 * main - Entry point
 * Description: computes sum of all
 * the multiples of 3 or 5
 * below 1024 (excluded)
 * Return: Always 0 (SuccesS)
 */
int main(void)
{
	int sum, num;

	for (num = 0; num < 1024; num++)
	{
		if ((num % 3 == 0) || (num % 5 == 0))
				sum += sum;
	}
	printf("%d\n", sum);
	return (0);
}
