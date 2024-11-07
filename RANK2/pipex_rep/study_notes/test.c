#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* Understanding Pipes and Forking
 *
 *  Purpose of Pipes:
 *      Pipes (pipe(fd)) are used for communication between a parent
 *      and a child process.
 *      The fd array you created with int fd[2]; represents the two ends
 *      of the pipe:
 *      	fd[0]: The read end of the pipe.
 *      	fd[1]: The write end of the pipe.
 *
 * Creating a Child Process:
 * 	fork() is used to create a new child process. The id variable
 * 	stores the return value of fork().
 * 		If fork() returns 0, you're in the child process.
 * 		If fork() returns a positive value, you're in the
 * 		parent process, and id contains the child’s process ID.
 */

int	main(void)
{
	int	*arr;
	int	arrSize;
	int	start;
	int	end;
	int	fd1[2];
	int	fd2[2];
	int	id1;
	int	id2;
	int	sum;
	int	i;
	int	totalSum;
	int	sumFromChild1;
	int	sumFromChild1ofChild;
	int	sumFromChild2;

	arr = malloc(100 * sizeof(int));
	if (arr == NULL)
		return (1);
	printf("\n\nThe sum of << arr[");
	i = -1;
	while (++i < 100)
	{
		arr[i] = i + 1;
		if (i != 0)
			printf("%d, ", i);
	}
	printf("%d] >>\n\n", i);
	arrSize = i;
	if (pipe(fd1) == -1)
		return (1);
	if (pipe(fd2) == -1)
		return (1);
	id1 = fork();
	if (id1 == -1)
		return (2);
	id2 = fork();
	if (id2 == -1)
		return (2);
/* 
 * The 'pipe(fd)' function tries to create a 'pipe' and store it's file
 * 	descriptors in the 'fd' array.
 * If pipe() succeeds, return will be '0', failure will be '-1',
 * 	'errno' is set to indicate the error.
 * In this case, return is just set to '1', it could be another error
 * 	code.
 * The 'fork()' function creates a new child process by duplicating
 * 	the current process.
 * 'fork()' returns;
 * 		'0' when in the child process,
 * 		the 'ID (positive int)' of the child's process
 * 		'-1' if the 'fork()' fails.
 * 		(in our case when 'fork()' fails, it returns '2'.
 */
	if (id1 == 0)
	{	
		if (id2 == 0)
		{
			start = 0;
			end = arrSize / 3;
			printf("\nI am the Child of Child 1\n");
		}
		else
		{
			start = arrSize / 3;
			end = start * 2;
			printf("\nI am the Child 1\n");
			while (wait(NULL) != -1 || errno != ECHILD)
				printf("\nwaiting for COC1\n");
		}

	}
	else
	{
		if (id2 == 0)
		{
			start = (arrSize / 3) * 2;
			end = arrSize;
			printf("\nI am the Child 2\n");
		}
		else
		{
			printf("\nI am the Parent\n");
			while (wait(NULL) != -1 || errno != ECHILD)
				printf("\nwaiting for C1C2\n");
		}
	}
	sum = 0;
	while (start < end)
	{
		sum += arr[start];
		start++;
	}
	if (id2 == 0)
		printf("\n\tCalculated sum: %d\n", sum);
	if (id1 == 0)
	{
		if (id2 == 0)
		{
			close(fd1[0]);
			if (write(fd1[1], &sum, sizeof(int)) == -1)
				return (3);
			close(fd1[1]);
		}
		else
		{
			if (read(fd1[0],
				&sumFromChild1ofChild,
				sizeof(int)) == -1)
				return (3);
			close(fd1[0]);
			sum += sumFromChild1ofChild;
			printf("\n\tCalculated sum of COC1 and C1: %d\n", sum);
			if (write(fd1[1], &sum, sizeof(int)) == -1)
				return (3);
			close(fd1[1]);
		}
	}
/* close(fd[0]): The child process does not need to read from the pipe,
 * 	so it closes the read end. This is a standard practice to
 * 	ensure no unintended operations happen on that end.
 * write(fd[1], &sum, sizeof(int)): The child process writes the
 * 	calculated sum to the write end of the pipe (fd[1]).
 * 	The write()function sends sizeof(int) bytes from sum into
 * 	the pipe.
 * close(fd[1]): After writing, the child closes the write end of the
 * 	pipe. This signals the parent process that no more data will
 * 	be written.
 */
	else
	{
		if (id2 == 0)
		{
			close(fd2[0]);
			if (write(fd2[1], &sum, sizeof(int)) == -1)
				return (4);
			close(fd2[1]);
		}	
		else
		{
			close(fd1[1]);
			close(fd2[1]);
			if (read(fd1[0],
				&sumFromChild1,
				sizeof(int)) == -1)
				return (4);
			close(fd1[0]);
			if (read(fd2[0],
				&sumFromChild2,
				sizeof(int)) == -1)
				return (4);
			close(fd2[0]);
			totalSum = sumFromChild1 + sumFromChild2;
			printf("\n\t\tTotal sum is %d\n", totalSum);
		}
	}
	return (0);
}

/* close(fd[1]): The parent process does not need to write to the pipe,
 * 	so it closes the write end.
 * read(fd[0], &sumFromChild, sizeof(int)): The parent process reads the
 * 	data sent by the child from the 'read end' of the pipe (fd[0]).
 * 	The data is stored in sumFromChild.
 * close(fd[0]): After reading, the parent closes the read end.
 * 	This is good practice to release resources.
 * totalSum = sum + sumFromChild: The parent process calculates
 * 	the totalSum by adding the sum calculated by itself and
 * 	the sum received from the child.
 * wait(NULL): The parent waits for the child process to finish
 * 	to ensure proper cleanup and synchronization.
 */
