/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:06 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 14:20:59 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*point_next_chank(char *token)
{
	if (!ft_strncmp(token, "$?", 2))
		return (token + 2);
	if (*token == '$')
	{
		token++;
		while (*token && !is_spacetab(*token) && *token != '$')
			token++;
		if (!*token)
			token = NULL;
	}
	else
		token = ft_strchr(token, '$');
	return (token);
}

// [MALLOC]
char	*get_current_chank(char *token)
{
	char	*start;
	char	*end;
	char	*chank;

	start = token;
	if (!point_next_chank(token))
		end = ft_strchr(token, '\n');
	else
		end = point_next_chank(token);
	chank = ft_substr(start, 0, end - start);
	return (chank);
}
