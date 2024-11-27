/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:34:54 by suroh             #+#    #+#             */
/*   Updated: 2024/11/27 00:49:48 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_127(const char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	exit(127);
}

void	error_exit(const char *msg)
{
	ft_putstr_fd(msg, 2);
	write(1, "\n", 1);
	exit(1);
}

/*
 * simple error msg
 * 	*/

int	get_child_exit_status(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

char	*find_loc(char *command, char **envp)
{
	char	**full_path;
	char	*bin_path;
	char	*path_tracker;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	full_path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (full_path[i])
	{
		path_tracker = ft_strjoin(full_path[i], "/");
		bin_path = ft_strjoin(path_tracker, command);
		free(path_tracker);
		if (access(bin_path, F_OK) == 0)
			return (bin_path);
		free(bin_path);
		i++;
	}
	i = -1;
	while (full_path[++i])
		free(full_path[i]);
	free(full_path);
	return (0);
}

void	execute(char *av, char **envp)
{
	char	**command;
	char	*location;
	int		i;

	if (!av || !*av)
	{
		ft_putstr_fd("Empty command ignored\n", STDERR_FILENO);
		exit(0);
	}
	command = ft_split(av, ' ');
	location = find_loc(command[0], envp);
	if (location == 0)
	{
		i = -1;
		while (command[++i])
			free(command[i]);
		free(command);
		error_127(av);
	}
	if (execve(location, command, envp) == -1)
		error_exit("Can't Execute");
}

/* ft_strnstr() will find if "PATH" is present at the beginning of a
 * 	string by searching each envp[i].
 * Then ft_split() will skip the "PATH=" part and splits the string with
 * 	':'.
 * 
 * for example:
 * envp[0] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
 *	full_path[0] = /usr/local/sbin
 *	path_tracker = /usr/local/sbin/
 *	bin_path = /usr/local/sbin/"command or av[2]".
 *
 *	In this case, the function access(bin_path, F_OK) would return
 *	-1. Which means that in that location or path,
 *	the command file is not found.
 *	if the first while loop is passed, it will eventually return
 *	0.
 *	*/
/* On error, execve() will return a -1. So if successfully ran, it will
 * execute command in the location.
 *
 * The flags of the command are handled properly because the execve()
 * function has the whole parameter of command.
 * 	*/
