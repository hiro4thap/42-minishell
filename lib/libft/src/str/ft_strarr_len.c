/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:43:47 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/08 12:15:10 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strarr_len(char **str_array)
{
	size_t	size;

	size = 0;
	while (str_array && *str_array)
		size += ft_strlen(*str_array++);
	return (size);
}
