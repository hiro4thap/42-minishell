/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:23 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/09 00:04:22 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

// Allocates memory for an array of 'nmemb' elements of size 'size' each and 0s.
// Caller must check if malloc failed.
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*output;
	size_t	total_size;

	if (size != 0 && nmemb > ULONG_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	output = malloc(total_size);
	if (!output)
		return (NULL);
	ft_memset((char *) output, '\0', total_size);
	return (output);
}
