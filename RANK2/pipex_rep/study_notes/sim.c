#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
/*
 * dup2(fd[1], STDOUT_FILENO):
 *     This redirects the standard output 
 *     (STDOUT_FILENO, which is typically the terminal)
 *     to the write end of the pipe (fd[1]).
 *     After this call, any data that the ping command writes to
 *     standard output will be sent to the pipe instead of the terminal.
 * 
 * dup2(fd[0], STDIN_FILENO):
 * 	this in contrast to the function on the top, duplicates the
 * 	read end to the executed function.
 *
 * execlp() does these things;
 * 	
 * 	Process Replacement: After execlp() is called successfully,
 * 		the original program ceases to exist in memory, and the
 * 		new program specified by execlp() begins executing in
 * 		the same process ID. The old code, stack, and heap of
 * 		the original program are discarded and replaced by the
 * 		new program's code and memory layout.
 * 	
 * 	No Return: If execlp() is successful, it never returns to
 * 		the calling code. Instead, the new program starts
 * 		executing from its main() function as if it were just
 * 		launched. If execlp() fails, it returns -1 and sets
 * 		errno to indicate the error.
 * 	
 * 	File Descriptors and Environment: The process retains its file
 * 		descriptors (unless explicitly closed) and the
 * 		environment variables unless modified by the
 * 		new program.
 * 	
 * 	pid_t pid = fork();
 * 	if (pid == 0)
 * 	{
 *	    // Child process
 *   		execlp("ls", "ls", "-l", NULL);
 *   		// Replaces the current process with 'ls -l'
 *		perror("execlp failed");
 *		// This line runs only if execlp fails
 * 		exit(1);
 *	}
 * Parent process continues here...
 *	
 *	BASICALLY, "execlp() function" REPLACES WHAT THE PROCESS SHOULD
 *	DO.
 *
 *	*** YOU ALSO HAVE TO CLOSE THE READ AND WRITE END OF THE MAIN
 *		PARENT PROCESS ***
 *
 * for example,
 * 	ping -c 5 google.c | grep rtt
 * 	ping is routed (stdout) to the pipe.
 * 	therefore, doesn't display 'program of ping'
 * 	the (stdin) is set to grep and it will take the output of
 * 	ping (stdout) and then run grep command.
 */

