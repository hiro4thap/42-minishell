/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:37:50 by hiono             #+#    #+#             */
/*   Updated: 2024/05/10 15:04:38 by hiono            ###   ########.fr       */
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

void	errprint(char *msg, char *fail)
{
	while (*msg)
	{
		while (*msg && *msg != '%')
		{
			ft_putchar_fd(*msg, 2);
			msg++;
		}
		if (*msg && !ft_strncmp(msg, "%s", 2))
		{
			ft_putstr_fd(fail, 2);
			msg++;
			msg++;
		}
	}
}

/// @brief 
/// @param str_array 
/// @return 
size_t	ft_arrlen(char **str_array)
{
	size_t	len;

	len = 0;
	while (*str_array)
	{
		len += 1;
		str_array++;
	}
	return (len);
}
