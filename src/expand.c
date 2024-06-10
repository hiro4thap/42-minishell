/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:54 by hiono             #+#    #+#             */
/*   Updated: 2024/06/10 15:39:35 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_chank(char	*token)
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

char	*get_var(char *dollar)
{
	char	*end;

	end = dollar + 1;
	if (*end == '?')
		return (ft_substr(dollar, 0, 2));
	if (!ft_isalpha(*end) && *end != '_')
		return (ft_strdup("$"));
	while (ft_isalnum(*end) || *end == '_')
		end++;
	return (ft_substr(dollar, 0, end - dollar));
}

char	*expand_var(char *expanded, char *var, t_environment *env)
{
	char	*value;
	char	*temp;

	if (!ft_strncmp(var, "$?", 3))
		value = ft_itoa(env->exit_code);
	else if (ft_strncmp(var, "$", 2) && get_value(env, var + 1))
		value = ft_strdup(get_value(env, var + 1));
	else
		value = NULL;
	if (value)
	{
		temp = replace_substr(expanded, var, value);
		free(value);
	}
	else
		temp = replace_substr(expanded, var, "");
	free(expanded);
	return (temp);
}

char	*expand_chank(char *chank, t_environment *env)
{
	char	*expanded;
	char	*dollar;
	char	*var;

	expanded = ft_strdup(chank);
	dollar = ft_strchr(chank, '$');
	while (dollar)
	{
		var = get_var(dollar);
		if (!ft_strncmp(var, "$", 2))
		{
			dollar = ft_strchr(dollar + 1, '$');
			continue ;
		}
		expanded = expand_var(expanded, var, env);
		free(var);
		dollar = ft_strchr(dollar + 1, '$');
	}
	free(chank);
	return (expanded);
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
		if (!str)
			temp = ft_strdup(trimmed);
		else
			temp = ft_strjoin(str, trimmed);
		free(str);
		str = temp;
		free(chank);
		free(trimmed);
	}
	return (str);
}
