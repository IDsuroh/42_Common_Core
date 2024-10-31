/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:09 by suroh             #+#    #+#             */
/*   Updated: 2024/08/22 16:04:20 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_after_line(char *line)
{
	char	*after_line;
	char	*temp;
	int		len;

	after_line = ft_strchr(line, '\n');
	if (!after_line)
	{
		free(line);
		return (NULL);
	}
	len = ft_strlen(after_line);
	temp = (char *)malloc(len);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, after_line + 1, len);
	if (temp[0] == '\0')
	{
		free(line);
		free(temp);
		return (NULL);
	}
	free(line);
	return (temp);
}
// the value that starts from \n is set to after_line
// malloc(len) only since after_line includes '\n'
// so malloc(len + 1) will result in extra space.
// ft_strlcpy will copy after_line + 1 till before '\0'
// then add '\0'.
// example:
//	after_line = \n f g \0
//		      0 1 2  3 = len
//
//	after_line + 1 = f g \0
//	ft_strlcpy has i < (3 - 1) == i < (2)
//	so until i = 1
//	then {f, g} then add '\0'; {f, g, \0}
// it is very important to put a safety measure for the
// after_line because of the possibility of
// after_line == NULL

static char	*print_current_line(char *line)
{
	int		i;
	char	*print_line;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i++] == '\n')
			break ;
	}
	print_line = (char *)malloc(i + 1);
	ft_strlcpy(print_line, line, i + 1);
	return (print_line);
}
// get until \n

static char	*get_current_line(char *line, int fd)
{
	ssize_t	read_check;
	char	*buff;
	char	*temp;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!line || !ft_strchr(line, '\n'))
	{
		read_check = read(fd, buff, BUFFER_SIZE);
		if (read_check <= 0)
			break ;
		buff[read_check] = '\0';
		if (!line)
			line = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(line, buff);
			free(line);
			line = temp;
		}
	}
	free(buff);
	return (line);
}
//1: signed version of size_t
//   can hold negative values as well as positive values.
//2: save memory size to buff
//3: while there is nothing in the 'line', or until there is not /n
//4: if read_check is a 0(		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}first read data is copied to line
//6: if line has data already, it gets new data from buff
//   the old line is freed and line is updated

char	*get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_current_line(line, fd);
	if (!line)
		return (NULL);
	next_line = print_current_line(line);
	line = get_after_line(line);
	return (next_line);
}
//set line to static to remain constantly
//if not readable and buff size is below 1
//value is the output of gcl func.
//get_current_line function gets value including the \n symbol.
//print_currect_line function get value until the \n symbol from gcl.

// int	main(void)
// {
// 	int	fd = open("file.txt", O_RDONLY);
// 	char	*line;
// 	line = get_next_line(fd);
// 	if (line == NULL)
// 		printf("NULL\n");
// 	while (line > 0)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }

// fd means file descriptor.
// by default or standard;
//	'0': Standard Input (stdin)
//	'1': Standard Output (stdout)
//	'2': Standard Error (stderr)
//Common Functions that Use File Descriptors:
//
//    open(): Opens a file and returns a file descriptor.
//    read(): Reads data from the file associated with the file descriptor.
//    write(): Writes data to the file associated with the file descriptor.
//    close(): Closes the file associated with the file descriptor,
//	       freeing the resource.
//
//
// need to update to git repository url to re upload.