/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:43:47 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/16 17:36:20 by jhughes          ###   ########.fr       */
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
		size += 1;
	return (size);
}
