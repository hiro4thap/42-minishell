/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:20:51 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:29:09 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns a copy of 's' with 'f' applied to each character based on its index.
// Caller must check if malloc failed.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	const size_t	size = ft_strlen(s);
	char			*output;
	int				index;

	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	index = 0;
	while (s[index])
	{
		output[index] = (*f)(index, s[index]);
		index++;
	}
	output[index] = '\0';
	return (output);
}
