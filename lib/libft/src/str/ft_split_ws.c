/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:28:24 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/16 17:35:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words_ws(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_isspace(*s))
			s++;
	}
	return (count);
}

static void	move_to_next_word_ws(const char *str, int *index)
{
	while (ft_isspace(str[*index]))
		(*index)++;
}

static char	*next_word_ws(const char *str, int *index)
{
	const int	start = *index;

	while (str[*index] && !ft_isspace(str[*index]))
		(*index)++;
	return (ft_substr(str, start, *index - start));
}

/// @brief Splits a string based on whitespace, using ft_isspace.
/// @param s The string to split.
/// @return NULL-terminated array of C strings, to be freed by caller.
char	**ft_split_ws(const char *s)
{
	const int	words = count_words_ws(s);
	const char	**output = malloc(sizeof(char *) * (words + 1));
	int			word;
	int			index;

	if (!output)
		return (NULL);
	word = 0;
	index = 0;
	while (s[index])
	{
		move_to_next_word_ws(s, &index);
		if (s[index] == '\0')
			break ;
		output[word] = next_word_ws(s, &index);
		if (output[word] == NULL)
		{
			ft_strarr_clear((char **) output);
			return (NULL);
		}
		word++;
	}
	output[word] = NULL;
	return ((char **) output);
}
