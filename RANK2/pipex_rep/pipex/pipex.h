/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:02:40 by suroh             #+#    #+#             */
/*   Updated: 2024/11/25 19:02:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "libft/libft.h"

//Struct to hold Arguments
typedef struct s_child_process_data
{
	char	**av;
	char	**envp;
	int		*fd;
	int		file;
	void	(*child_func)(char **, char **, int*, int);
}	t_data;

//Struct to hold pipex_values
typedef struct s_pipex
{
	int		fd[2];
	int		filein;
	int		fileout;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

//utility functions
void	error_exit(const char *msg);
void	error_127(const char *msg);
void	execute(char *av, char **envp);
char	*find_loc(char *command, char **envp);
int		get_child_exit_status(pid_t pid);

//main functions
void	child_process(char **av, char **envp, int *fd, int filein);
void	parent_process(char **av, char **envp, int *fd, int fileout);

#endif
