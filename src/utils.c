/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:37:50 by hiono             #+#    #+#             */
/*   Updated: 2024/05/09 17:36:40 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*trim_quote(char *token)
{
	int		len;
	char	*res;

	len = ft_strlen(token);
	res = token;
	if (token[0] == '\'' && token[len - 1] == '\'')
	{
		res = ft_strtrim(token, "\'");
		free(token);
	}
	else if (token[0] == '\"' && token[len - 1] == '\"')
	{
		res = ft_strtrim(token, "\"");
		free(token);
	}
	return (res);
}
