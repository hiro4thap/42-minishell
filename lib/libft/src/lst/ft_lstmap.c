/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:13:12 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:03:48 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a new linked list in which 'f' has been applied to every element.
// Caller must check if malloc failed.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*node;
	void	*mapped_content;

	if (!lst || !f || !del)
		return (NULL);
	output = NULL;
	while (lst)
	{
		mapped_content = (*f)(lst->content);
		node = ft_lstnew(mapped_content);
		if (!node)
		{
			(*del)(mapped_content);
			ft_lstclear(&output, del);
			return (NULL);
		}
		ft_lstadd_back(&output, node);
		lst = lst->next;
	}
	return (output);
}
