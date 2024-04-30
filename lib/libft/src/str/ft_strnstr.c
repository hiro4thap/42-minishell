/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:48 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:27:54 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns pointer to s2 in the first n bytes of s1, NULL if not found.
char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	const size_t	str_size = ft_strlen(s2);

	if (!(*s2))
		return ((char *) s1);
	while (*s1 && n >= str_size)
	{
		if (ft_strncmp(s1, s2, str_size) == 0)
			return ((char *) s1);
		s1++;
		n--;
	}
	return (NULL);
}
