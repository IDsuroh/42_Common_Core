/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:42:05 by suroh             #+#    #+#             */
/*   Updated: 2024/11/17 14:49:18 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **envp, int *fd)
{
	int	ghostfile;
	int	filein;

	filein = open(av[1], O_RDONLY);
	if (filein == -1)
		error_suc(av[1]);
	dup2(fd[1], STDOUT_FILENO);
	if (dup2(filein, STDIN_FILENO) == -1)
	{
		close(filein);
		ghostfile = open("ghost", O_CREAT);
		dup2(ghostfile, STDIN_FILENO);
		close(ghostfile);
		unlink("ghost");
	}
	close(filein);
	close(fd[0]);
	close(fd[1]);
	execute(av[2], envp);
}

/* 
 * Why Use dup2()?
 *
 *   Simplicity in Command Execution:
 *       With dup2(), you can redirect the pipe or file directly to
 *       stdin or stdout.
 *       This allows subsequent commands (execve) to work seamlessly with the
 *       standard input/output streams.
 *   Avoids Manual Read/Write Loops:
 *       By setting up the redirections, you don't need explicit read()
 *       and write() loops in your code to transfer data between processes.
 *
 * The combination of these dup2() calls sets up the process so that:
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
	int		fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error_exit(av[4]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	close(fd[1]);
	close(fd[0]);
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
			error_exit("pipe failed");
		pid = fork();
		if (pid == -1)
			error_exit("fork failed");
		if (pid == 0)
			child_process(av, envp, fd);
		waitpid(pid, NULL, 0);
		parent_process(av, envp, fd);
	}
	else
		ft_putstr_fd("\n\t\t\033[31mError: Wrong Format\n\n\e[0m", 2);
}
/*
 * In this project we are asked to code a program which will immitate
 * the behavior of this shell command: ❯ < file1 cmd1 | cmd2 > file2
 *	
 *	The idea of the program is that we take an infile and two commands,
 *	and pass the infile as the standard input to the first command, and then
 *	pipe the output of the first command to the second command, and finally
 *	save it all to a second file. 
 *
 * Symbol Meaning:
 *	
 *	<: Used to denote that we will be passing the next argument as
 *		the standard input (stdin)
 *
 * 	file1: Path to the file we want to open as the standard input.
 * 		It must exist and should be opened read-only
 * 
 * 	cmd1: First command. It will receive the stdin and run a command with it,
 * 		if applicable
 * 
 * 	|: Transforms the standard output (stdout) of the first command (cmd1) into
 * 		the standard input (stdin) for the next command (cmd2)
 * 
 * 	cmd2: Receives the standard output of the first command (cmd1) as stdin and
 * 		runs a command with it, if applicable
 *
 * 	>: Redirects whatever is on the standard output (stdout) into a file,
 * 		creating it if it does not exist
 * 
 * 	file2: Path to an output file which may or may not exist. If it exists,
 * 		it will be truncated (emptied) and should be opened write-only
 *
 *
 *
 * Clarification on How envp Works at Program Start:
 *
 * When a program is executed (e.g., from a shell or as a system
 * process), the operating system prepares the environment variables
 * and passes them to the program.
 * The envp array is populated automatically by the operating system
 * with all the environment variables that were present at the time
 * the program was started.
 *
 * the envp parameter is automatically recognized.
 * the envp pointer array holds all the environment variables that
 * are set in the system at the time of the program's execution.
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
 * What Does waitpid(pid, NULL, 0) Do?
 *
 *	In the code waitpid(pid, NULL, 0), you're telling the parent process to:
 *
 *   Wait for the child with the process ID pid to terminate.
 *   Do nothing with the exit status of the child
 *   	(since the second argument is NULL).
 *   Block the parent until the child process finishes
 *   	(since options is set to 0).
 *
 * If you don't pass envp when using execve():
 *
 *	The command being executed might fail if it relies on any
 *	environment variable, such as PATH.
 *	The new process may not run in the intended environment,
 *	potentially causing errors or unexpected behavior.
 *
 * Large file sizes can cause a pipe deadlock. Data that the pipe can hold is
 * typically 64 KB.
 * 	*/
