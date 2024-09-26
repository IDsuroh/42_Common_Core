/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:41:26 by suroh             #+#    #+#             */
/*   Updated: 2024/04/24 18:27:58 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_blockcounter(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			counter++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (counter);
}

static char	**ft_free(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(str[i++]);
	free(str);
	return (NULL);
}

static const char	*ft_skipper(const char *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

char	**ft_split(const char *s, char c)
{
	char	**mem;
	int		i;
	int		count;
	int		blockcount;

	blockcount = ft_blockcounter(s, c);
	mem = (char **)ft_calloc(sizeof(char *), (blockcount + 1));
	if (!mem || !s)
		return (NULL);
	i = 0;
	while (i < (blockcount))
	{
		count = 0;
		s = ft_skipper(s, c);
		while (s[count] && s[count] != c && s[count] != '\0')
			count++;
		mem[i] = (char *)ft_calloc(sizeof(char), (count + 1));
		if (!mem[i])
			return (ft_free(mem, i));
		ft_memmove(mem[i], s, count); // would put 'ft_memcpy' because there is no memory overlap in the first place.
		mem[i++][count] = '\0';
		s += count;
	}
	mem[i] = NULL;
	return ((char **)mem);
}

// int	main()
// {
// 	char	*str = "ab__42cd__dfgdfg";
// 	char	c = '_';

// 	// int	times = ft_blockcounter(str, c);
// 	char	**new = ft_split(str, c);

// 	int i = 0;
// 	while (new[i] != NULL)
// 	{
// 		//printf("bad\n");
// 		printf("My token %d: %s \n", i, new[i]);

// 		free(new[i]);
// 		i++;
// 	}
// 	//printf("\nyousuck; the output should be {ab, cd, ef}");
// 	free (new);
// 	new = NULL;

// 	return (0);
// }
