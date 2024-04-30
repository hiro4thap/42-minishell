/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:25 by jhughes           #+#    #+#             */
/*   Updated: 2024/02/21 19:49:10 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Sets n bytes of s to '\0'.
void	ft_bzero(void *s, size_t n)
{
	char			*str;
	unsigned int	index;

	index = 0;
	str = (char *) s;
	while (index < n)
	{
		str[index] = '\0';
		index++;
	}
}
