/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:42:05 by suroh             #+#    #+#             */
/*   Updated: 2024/11/12 19:55:41 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
		error_msg();
	dup2(filein, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execute(av[2], envp);
}

/* The combination of these dup2() calls sets up the process so that:
 *
 * Reading: The process reads from the input file (av[1]) because
 * 	STDIN_FILENO is now connected to filein.
 * Writing: The process writes to the pipe (instead of stdout) because
 * 	STDOUT_FILENO is now connected to fd[1].
 *
 * 0777: is a file permission mode (in octal format). This argument
 * 	is used when creating a new file if it doesn't exist.
 * 	The mode 0777 grants full read, write, and execute permissions
 * 	to the file for the owner, group, and others.
 * Note: In the context of opening an existing file, the third
 * 	argument (permissions) is usually ignored.
 * 	It is only used when creating a new file, where it specifies
 * 	the permissions for the newly created file.
 * 	*/

void	parent_process(char **av, char **envp, int *fd)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error_msg();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(av[3], envp);
}

/* fd[0] = the read end is duplicated to the STDIN and then printed
 * out to the duplicated STDOUT which is from fileout. The file that
 * is opened and is able to write-only, create if not-exist, truncate
 * (O_TRUNC will erase any data in the file as soon as the file gets
 * opened).
 *	*/

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error_msg();
		pid = fork();
		if (pid == -1)
			error_msg();
		if (pid == 0)
			child_process(av, envp, fd);
		wait(NULL);
		parent_process(av, envp, fd);
	}
	else
	{
		ft_putstr_fd("\n\t\t\033[31mError: Wrong Format\n\e[0m", 2);
		ft_putstr_fd("\t./pipex <file1> <cmd1> <cmd2> <file2>\n\n", 1);
	}
}

/* Clarification on How envp Works at Program Start:
 *
 * When a program is executed (e.g., from a shell or as a system
 * process), the operating system prepares the environment variables
 * and passes them to the program.
 * The envp array is populated automatically by the operating system
 * with all the environment variables that were present at the time
 * the program was started.
 *
 * envp[0] = "PATH=/usr/bin:/bin";
 * envp[1] = "USER=exampleuser";
 * envp[2] = "HOME=/home/exampleuser";
 * envp[3] = "SHELL=/bin/bash";
 * envp[4] = "LANG=en_US.UTF-8";
 * envp[5] = "TERM=xterm-256color";
 * // More environment variables could be here...
 * envp[N] = NULL; // Marks the end of the array
 * 
 * Most modern operating systems (e.g., Linux, macOS) will populate
 * envp with some basic environment variables like PATH, USER, and
 * HOME by default when a program starts.
 *
 * Execution with Context: By passing envp to the execve() call,
 * 	your program ensures that cmd1 and cmd2 have access to all
 * 	the environment variables they need to function correctly.
 * 	Without envp, the new program might not have the correct paths
 * 	or environment settings, leading to issues like
 * 	"command not found" or unexpected behavior.
 * Consistency: Using envp maintains consistency between how your
 * 	pipex program runs the commands and how the shell would execute
 * 	them.
 *
 * If you don't pass envp when using execve():
 *
 *	The command being executed might fail if it relies on any
 *	environment variable, such as PATH.
 *	The new process may not run in the intended environment,
 *	potentially causing errors or unexpected behavior.
 */
