/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:42:05 by suroh             #+#    #+#             */
/*   Updated: 2024/11/10 23:13:29 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		putstr_fd("\n\t\t\033[31mError: Wrong Format\n\e[0m", 2);
		putstr_fd("\t./pipex <file1> <cmd1> <cmd2> <file2>\n\n", 1);
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
