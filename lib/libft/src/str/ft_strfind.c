/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:37:12 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/06 11:14:40 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Finds the position of string ``needle`` in the string ``haystack``.
/// @param haystack The string to search in.
/// @param needle The string to find in ``haystack``.
/// @return Index of start of ``needle`` in ``haystack``, ``-1`` if not found.
/// @todo Test, ensuring different compartive sizes of ``haystack`` and 
/// ``needle`` are handled, and search_size works appropriately.
int	ft_strfind(char *haystack, char *needle)
{
	int	index;
	int	search_size;
	int	needle_size;

	if (!haystack || !needle)
		return (-1);
	index = 0;
	needle_size = ft_strlen(needle);
	search_size = ft_strlen(haystack) - needle_size;
	while (index <= search_size)
	{
		if (ft_strncmp(haystack + index, needle, needle_size) == 0)
			return (index);
		index++;
	}
	return (-1);
}
