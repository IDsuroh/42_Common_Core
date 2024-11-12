/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:02:40 by suroh             #+#    #+#             */
/*   Updated: 2024/11/12 22:04:31 by suroh            ###   ########.fr       */
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

//utility functions
void	error_msg(void);
void	execute(char *av, char **envp);
char	*find_loc(char *command, char **envp);

//main functions
void	child_process(char **av, char **envp, int *fd);
void	parent_process(char **av, char **envp, int *fd);

#endif
