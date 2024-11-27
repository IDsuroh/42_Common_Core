/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:29:47 by suroh             #+#    #+#             */
/*   Updated: 2024/11/26 21:32:46 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_reader(int fd_in)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		ft_putstr_fd("malloc failed", 2);
		return ;
	}
	bytes_read = read(fd_in, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		write(STDOUT_FILENO, buffer, bytes_read);
		bytes_read = read(fd_in, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		ft_putstr_fd("read failed", 2);
	free(buffer);
}
