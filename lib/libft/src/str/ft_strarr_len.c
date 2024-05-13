/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:43:47 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/13 11:08:59 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strarr_len(char **str_array)
{
	size_t	size;

	if (!str_array)
		return (-1);
	size = 0;
	while (str_array[size])
	{
		char *blah = str_array[size];
		(void) blah;
		size += 1;
	}
	return (size);
}
