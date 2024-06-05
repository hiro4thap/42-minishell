/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:01:41 by hiono             #+#    #+#             */
/*   Updated: 2024/06/04 13:12:08 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strchrout(const char *str, const char *quotes, char c)
{
	const char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == c)
			return ((char *) tmp);
		if (is_in(quotes, *tmp) && ft_strchr(tmp + 1, *tmp))
			tmp = ft_strchr(tmp + 1, *tmp);
		tmp++;
	}
	return (NULL);
}
