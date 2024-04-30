/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:01 by jhughes           #+#    #+#             */
/*   Updated: 2024/04/15 08:46:45 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void	move_to_next_word(const char *str, int *index, char c)
{
	while (str[*index] == c)
		(*index)++;
}

static char	*next_word(const char *str, int *index, char c)
{
	const int	start = *index;

	while (str[*index] && str[*index] != c)
		(*index)++;
	return (ft_substr(str, start, *index - start));
}

// Splits 's' into words with 'c' as the delimiter.
// Returns an NULL-terminated array of C strings.
// Caller must check if malloc failed.
char	**ft_split(const char *s, char c)
{
	const int	words = count_words(s, c);
	const char	**output = malloc(sizeof(char *) * (words + 1));
	int			word;
	int			index;

	if (!output)
		return (NULL);
	word = 0;
	index = 0;
	while (s[index])
	{
		move_to_next_word(s, &index, c);
		if (s[index] == '\0')
			break ;
		output[word] = next_word(s, &index, c);
		if (output[word] == NULL)
		{
			ft_strclear((char **) output);
			return (NULL);
		}
		word++;
	}
	output[word] = NULL;
	return ((char **) output);
}
