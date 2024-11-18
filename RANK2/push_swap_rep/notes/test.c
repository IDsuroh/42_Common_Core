#include <stdio.h>

int	main(void)
{
	int	i;
	int	j;
	int	n;

	printf("Enter a positive integer: ");
	scanf("%d", &n);
	if (n > 10)
		printf("This might take a while...\n");
	i = 1;
	while (i <= n)
	{
		j = 1;
		while (j <= i)
		{
			printf("%d ", i * j);
			j++;
		}
		i++;
		printf("\n");
	}
	printf("DONE!\n");
	return (0);
}
