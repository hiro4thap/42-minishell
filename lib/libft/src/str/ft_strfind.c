/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:37:12 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/08 11:03:55 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Finds the position of string ``needle`` in the string ``haystack``.
/// @param haystack The string to search in.
/// @param needle The string to find in ``haystack``.
/// @return Index of start of ``needle`` in ``haystack``, ``-1`` if not found.
/// If ``needle`` is the empty string, returns 0.
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

/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	printf("<NULL, NULL> = %d\n", ft_strfind(NULL, NULL));
	printf("<Hello, NULL> = %d\n", ft_strfind("Hello", NULL));
	printf("<NULL, H> = %d\n", ft_strfind(NULL, "H"));
	printf("<Hello, H> = %d\n", ft_strfind("Hello", "H"));
	printf("<Hello, l> = %d\n", ft_strfind("Hello", "l"));
	printf("<H, Hello> = %d\n", ft_strfind("H", "Hello"));
	printf("<Hello, Hell> = %d\n", ft_strfind("Hello", "Hell"));
	printf("<Hello, lo> = %d\n", ft_strfind("Hello", "lo"));
	printf("<Hello, Hello> = %d\n", ft_strfind("Hello", "Hello"));
	printf("<Hello, ello> = %d\n", ft_strfind("Hello", "ello"));
	printf("<\"\", \"\"> = %d\n", ft_strfind("", ""));
	printf("<Hello, hello> = %d\n", ft_strfind("Hello", "hello"));
	printf("<Hello, ell> = %d\n", ft_strfind("Hello", "ell"));
	printf("<Hello, ellow> = %d\n", ft_strfind("Hello", "ellow"));
	printf("<Hello, ellb> = %d\n", ft_strfind("Hello", "ellb"));
	printf("<Hello, elb> = %d\n", ft_strfind("Hello", "elb"));
	printf("<Hello, \"\"> = %d\n", ft_strfind("Hello", ""));
	printf("<\"\", Hello> = %d\n", ft_strfind("", "Hello"));
	char *str = "Hello";
	printf("%p -> %p\n", str, strstr(str, ""));
}
*/
