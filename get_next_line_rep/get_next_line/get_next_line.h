/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:54:08 by suroh             #+#    #+#             */
/*   Updated: 2024/08/19 11:11:50 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H //if condition for the macros and set library
# define GET_NEXT_LINE_H //define library

# ifndef BUFFER_SIZE //if buffer not set
#  define BUFFER_SIZE 10 //set buffer to whatever value
# endif //end if

# include <fcntl.h> //including the necessary libraries
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

char		*get_next_line(int fd);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(const char *s1, const char *s2);

#endif