/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:54 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:26:16 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies 'src' to the end of a 'dst' of size 'sz', ensuring '\0' terminator.
// Returns the size of 'src' for the user to check for truncated result.
size_t	ft_strlcpy(char *dst, const char *src, size_t sz)
{
	size_t	index;

	index = 0;
	while (sz != 0 && index < sz - 1)
	{
		if (src[index] == '\0')
			break ;
		dst[index] = src[index];
		index++;
	}
	if (sz != 0)
		dst[index] = '\0';
	return (ft_strlen(src));
}
