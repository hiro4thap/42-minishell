/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:54 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 13:41:36 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_chank(char	*token)
{
	char	*end;

	if (is_quote(*token))
	{
		end = ft_strchr(token + 1, *token);
		if (!end)
			end = token;
		end++;
	}
	else
	{
		end = token;
		while (*end && !is_quote(*end))
			end++;
	}
	return (ft_substr(token, 0, end - token));
}

static char	*free_vars(void *ptr1, void *ptr2, void *ptr3)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	return (NULL);
}

/// @brief handle token by expanding variable and trimming quotes
/// @param token a token that needs to be expanded
/// @param env environment variable
/// @return expnaded and quotes-trimmed string
char	*expand_token(char *token, t_environment *env)
{
	char	*str;
	char	*chank;
	char	*trimmed;
	char	*temp;

	str = NULL;
	while (*token)
	{
		chank = get_chank(token);
		token += ft_strlen(chank);
		if (chank[0] != '\'' && chank[ft_strlen(chank) - 1] != '\'')
			chank = expand_chank(chank, env);
		trimmed = trim_quote(chank);
		if (!trimmed)
			return (free_vars(chank, NULL, NULL));
		if (!str)
			temp = ft_strdup(trimmed);
		else
			temp = ft_strjoin(str, trimmed);
		free_vars(str, chank, trimmed);
		if (!temp)
			return (NULL);
		str = temp;
	}
	return (str);
}
