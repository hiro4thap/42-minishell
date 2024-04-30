/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:12:45 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/08 23:59:04 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees the content of each element using 'del', before freeing the elemtent.
// The point to the start ('lst') is set to NULL.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*future;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		future = current->next;
		ft_lstdelone(current, del);
		current = future;
	}
	*lst = NULL;
}
