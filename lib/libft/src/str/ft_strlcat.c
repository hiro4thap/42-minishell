/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:56 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:24:13 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds 'src' to the end of 'dst' of size 'sz', provided there is space.
// Returns the size of 'dst' + 'src' for the user to check for truncated result.
size_t	ft_strlcat(char *dst, const char *src, size_t sz)
{
	const size_t	dst_size = ft_strlen(dst);
	const size_t	total_bytes = sz - dst_size - 1;
	size_t			count;
	size_t			index;

	if (sz <= dst_size)
		return (sz + ft_strlen(src));
	count = 0;
	index = dst_size;
	while (count < total_bytes && src[count])
		dst[index++] = src[count++];
	dst[index] = '\0';
	return (dst_size + ft_strlen(src));
}
