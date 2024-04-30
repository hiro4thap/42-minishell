/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 08:38:35 by jhughes           #+#    #+#             */
/*   Updated: 2024/04/15 08:43:04 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees all elements of a NULL terminated string array
void	ft_strclear(char **str_array)
{
	int	index;

	index = 0;
	while (str_array[index])
	{
		free(str_array[index]);
		str_array[index] = NULL;
		index++;
	}
	free(str_array);
}
