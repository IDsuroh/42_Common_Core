/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:07 by suroh             #+#    #+#             */
/*   Updated: 2024/05/04 16:36:47 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

// int	main(void)
// {
// 	t_list	*new;
// 	t_list	*new1;
// 	new = ft_lstnew("HI");
// 	new1 = ft_lstnew("string");
// 	printf("original '%s'\n", (char *)new1->content);
// 	ft_lstadd_back(&new1, new);
// 	printf("new1's new '%s'\n", (char *)new1->content);
// 	printf("new1's next '%s'\n", (char *)new1->next->content);
// 	while (new1 != NULL)
// 	{
// 		t_list	*temp = new1->next;
// 		free(new1);
// 		new1 = temp;
// 	}
// 	return (0);
// }