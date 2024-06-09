/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:44 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/09 22:52:54 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(const char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

// Returns copy of s1 with any characters in s2 trimmed from the start and end.
// Caller must check if malloc failed.
char	*ft_strtrim(char const *s1, char const *s2)
{
	char	*output;
	int		start;
	int		end;

	if (s1[0] == '\0')
		return (ft_strdup(s1));
	start = 0;
	while (is_in(s1[start], s2))
		start++;
	end = ft_strlen(s1) - 1;
	while (is_in(s1[end], s2))
		end--;
	output = ft_substr(s1, start, end - start + 1);
	return (output);
}
