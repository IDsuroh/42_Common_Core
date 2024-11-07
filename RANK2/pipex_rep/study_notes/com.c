#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(void)
{
	int	fd[2];
	int	id;
	int	x;
	int	y;

	if (pipe(fd) == -1)
	{
		printf("\nError with opening pipe\n");
		return (1);
	}
	id = fork();
	if (id < 0)
	{
		printf("\nError with forking\n");
		return (1);
	}
	if (id == 0)
	{
		close(fd[0]);
		printf("Input a number: ");
		scanf("%d", &x);
		write (fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		wait(NULL);
		printf("Value from child process %d\n", y);
	}
	return (0);
}
