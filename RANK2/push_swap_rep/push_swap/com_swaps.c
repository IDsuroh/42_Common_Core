/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_swaps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:19:47 by suroh             #+#    #+#             */
/*   Updated: 2024/11/29 21:06:37 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack_node **head)
{
	int	len;

	len = stack_len(*head);
	if (*head == NULL || head == NULL || len == 1)
		return ;
	*head = (*head)->links.next;
	(*head)->links.prev->links.prev = *head;
	(*head)->links.prev->links.next = (*head)->links.next;
	if ((*head)->links.next)
		(*head)->links.next->links.prev = (*head)->links.prev;
	(*head)->links.next = (*head)->links.prev;
	(*head)->links.prev = NULL;
}

void	sa(t_stack_node **a, bool checker)
{
	swap(a);
	if (!checker)
		write(1, "sa\n", 3);
}

// swap the first 2 elements at the top of stack a.

void	sb(t_stack_node **b, bool checker)
{
	swap(b);
	if (!checker)
		write(1, "sb\n", 3);
}

//Swap the first 2 elements at the top of stack b.

void	ss(t_stack_node **a, t_stack_node **b, bool checker)
{
	swap(a);
	swap(b);
	if (!checker)
		write(1, "ss\n", 3);
}

//sa and sb at the same time.
// +------+     +------+     +------+     +------+
// | Head | --> |  A   | <-> |  B   | <-> |  C   | <-> ...
// +------+     +------+     +------+     +------+
//                 ^             ^
//                 |             |
//           links.prev    links.next
//
//     *head points to A.
//     A->links.next points to B.
//     B->links.prev points to A.
//
// *head = (*head)->links.next;
// +------+  -  +------+ - + +------+ - + +------+ - +
// | NULL | <-> |  A   | <-> |  B   | <-> | NULL | <-> ...
// +------+     +------+     +------+     +------+
//                 				^
//                 				|
//           				New *head
//
// (*head)->links.prev->links.prev = *head;
// +------+ -	+------+ -   +------+ - + +------+ - + +------+
// | NULL |	<-A	|  B   | <-- |  A   | <-> |  B   | <-> | NULL  | <-> ...
// +------+     +------+     +------+     +------+	   +------+
//                 				^             ^
//                 				|			  |
//           			 B->links.prev	  New *head       
//
//     Update A->links.prev to point back to B:
//
// (*head)->links.prev->links.next = (*head)->links.next;
// +------+ -	+------+ -   +------+ -   +------+ - + +------+
// | NULL |	<-A	|  B   | <-- |  A   | <-- |  B   | <-> | NULL |
// +------+     +------+     +------+ ->C +------+	   +------+
//                 				^             ^
//                 				|			  |
//           			 B->links.prev	  New *head   
//
//     	Update A->links.next to point to C:
// 		B is now skipped in A->links.next.
//
// if ((*head)->links.next)
//     (*head)->links.next->links.prev = (*head)->links.prev;
// +------+ -	+------+ -   +------+ -   +------+   + +------+
// | NULL |	<-A	|  B   | <-- |  A   | <-- |  B   | --> |  C   | <-> ...
// +------+     +------+     +------+ ->C +------+ A<- +------+
//                 				^             ^			  ^
//                 				|			  |			  |
//           			 B->links.prev	  New *head      C->links.prev is A
//
//     (*head)->links.next refers to C.
//     Update C->links.prev to point back to A:
//
// (*head)->links.next = (*head)->links.prev;
// +------+ -	+------+ -   +------+ -   +------+   + +------+ - + +------+
// | NULL |	<-A	|  B   | <-- |  A   | <-- |  B   | --> |  A	  |		| NULL |
// +------+     +------+     +------+ ->C +------+     +------+		+------+
//                 				^             ^			  
//                 				|			  |			  
//           			 B->links.prev	  New *head      
// +------+ -	+------+ -      + +------+ - + +------+
// | NULL |	<-A	|  B   | <--  --> |  A	 |	   | NULL |
// +------+     +------+          +------+	   +------+
//              	^            			  
//              	|			 		  
//           	New *head 
//
//     Update B->links.next to point to A:
//
// (*head)->links.prev = NULL;
// +------+     +------+     +------+     +------+
// | NULL | <-> |  B   | <-> |  A   | <-> |  C   | <-> ...
// +------+     +------+     +------+     +------+
//                 ^
//                 |
//           New *head