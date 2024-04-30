/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:22:01 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns new string with s1 and s2 concatentated.
// Caller must check if malloc failed.
char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	size = ft_strlen(s1) + ft_strlen(s2);
	char			*output;
	int				index;

	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	index = 0;
	while (*s1)
	{
		output[index] = *s1;
		s1++;
		index++;
	}
	while (*s2)
	{
		output[index] = *s2;
		s2++;
		index++;
	}
	output[index] = '\0';
	return (output);
}
