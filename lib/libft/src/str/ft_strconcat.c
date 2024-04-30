/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:33:42 by jhughes           #+#    #+#             */
/*   Updated: 2024/04/15 11:10:46 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

// Creates a copy of argv and counts the NULL terminated list of arguments.
static int	count_args(va_list argv)
{
	va_list	copy;
	int		count;
	char	*str;

	va_copy(copy, argv);
	count = 1;
	str = va_arg(copy, char *);
	while (str)
	{
		str = va_arg(copy, char *);
		count++;
	}
	va_end(copy);
	return (count);
}

// Returns a string array with str and all the arguments in argv.
// Undefined behaviour if 0 argumgents in argv.
static char	**import_args(char *str, va_list argv)
{
	const int	count = count_args(argv);
	char		**array;
	int			index;

	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	*array = str;
	index = 1;
	while (index < count)
	{
		array[index] = va_arg(argv, char *);
		if (!array[index])
		{
			free(array);
			va_end(argv);
			return (NULL);
		}
		index++;
	}
	va_end(argv);
	array[index] = NULL;
	return (array);
}

// Concatenates 2 or more strings into a malloced string.
// Undefined result if less than two parameters are given.
// Caller must check for malloc fail.
char	*ft_strconcat(char *str, ...)
{
	va_list	argv;
	char	**array;
	int		index;
	int		size;
	char	*output;

	va_start(argv, str);
	array = import_args(str, argv);
	if (!array)
		return (NULL);
	size = ft_strarrlen(array);
	output = malloc(sizeof(char) * (size + 1));
	if (!output)
	{
		free(array);
		return (NULL);
	}
	index = 0;
	output[0] = '\0';
	while (array[index])
		ft_strlcat(output, array[index++], -1);
	free(array);
	return (output);
}
