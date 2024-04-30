/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:07:13 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies n bytes from 'src' to 'dest'.
// 'dest' and 'src' should not overlap, and are assumed to be size n.
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	index;

	if (!dest && !src)
		return (NULL);
	index = 0;
	while (index < n)
	{
		((char *) dest)[index] = ((char *) src)[index];
		index++;
	}
	return (dest);
}
