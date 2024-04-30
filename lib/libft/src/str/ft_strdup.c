/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:17:52 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:20:06 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a new copy of s.
// Caller must check if malloc failed.
char	*ft_strdup(const char *s)
{
	const size_t	size = ft_strlen(s);
	char			*output;
	int				index;

	output = (char *) malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	index = 0;
	while (s[index])
	{
		output[index] = s[index];
		index++;
	}
	output[index] = '\0';
	return (output);
}
