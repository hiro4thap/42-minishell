/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:07:55 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies n bytes from 'src' to 'dest'.
// 'dest' and 'src' may overlap and are assumed to be size n.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	direction;
	int	target;
	int	index;

	if (!dest && !src)
		return (NULL);
	index = 0;
	target = n;
	direction = 1;
	if (dest > src)
	{
		index = n - 1;
		target = -1;
		direction = -1;
	}
	while (index != target)
	{
		((char *) dest)[index] = ((char *) src)[index];
		index += direction;
	}
	return (dest);
}
