/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:15 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:07:03 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies n bytes from 'src' to 'dest', unless 'c' is encountered first.
// 'dest' and 'src' should not overlap, and are assumed to be size n.
void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*s_dest;
	char	*s_src;

	s_dest = (char *) dest;
	s_src = (char *) src;
	i = 0;
	while (i < n && s_src[i] != c)
	{
		s_dest[i] = s_src[i];
		i++;
	}
	if (s_src[i] == c)
	{
		s_dest[i] = s_src[i];
		return (dest + i + 1);
	}
	else
		return (NULL);
}
