/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:05:41 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:28:45 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a substring of s, starting from start for len characters.
// Caller must check if malloc failed.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*output;
	size_t			s_size;
	unsigned int	index;

	if (start > ft_strlen(s))
		s_size = 0;
	else
		s_size = ft_strlen(&s[start]);
	if (len < s_size)
		s_size = len;
	output = malloc(sizeof(char) * (s_size + 1));
	if (!output)
		return (NULL);
	index = 0;
	while (index < s_size)
	{
		output[index] = s[start + index];
		index++;
	}
	output[index] = '\0';
	return (output);
}
