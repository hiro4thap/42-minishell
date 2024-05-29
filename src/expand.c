/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:53:54 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 14:19:32 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// [MALLOC]
char	*expand_variable(char *chank, t_environment *env)
{
	const char	*expanded_value;

	if (*chank != '$' || ft_strlen(chank) == 1)
		return (ft_strdup(chank));
	else if (!ft_strncmp(chank, "$?", 3))
		return (ft_itoa(env->exit_code));
	expanded_value = get_value(env, chank + 1);
	if (!expanded_value)
		return (ft_strdup(""));
	return (ft_strdup(expanded_value));
}

int	count_chanks(char *token)
{
	int	len;

	len = 0;
	while (token && *token)
	{
		len++;
		token = point_next_chank(token);
	}
	return (len);
}

char	**split_token(char *token, t_environment *env)
{
	int		len;
	char	*chank;
	char	**chanks;
	int		i;

	len = count_chanks(token);
	chanks = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		chank = get_current_chank(token);
		chanks[i] = expand_variable(chank, env);
		token = point_next_chank(token);
		free(chank);
		i++;
	}
	chanks[i] = NULL;
	return (chanks);
}

/// @brief handle token by expanding variable and trimming quotes
/// @param token a token that needs to be expanded
/// @param env environment variable
/// @return expnaded and quotes-trimmed string
char	*expand_variables(char *token, t_environment *env)
{
	char	*trimmed_token;
	char	**chanks;
	size_t	i;
	char	*expanded_token;
	char	*temp;

	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
		return (trim_quote(token));
	trimmed_token = trim_quote(token);
	chanks = split_token(trimmed_token, env);
	i = 0;
	expanded_token = "";
	while (i < ft_strarr_len(chanks))
	{
		temp = ft_strjoin(expanded_token, chanks[i]);
		expanded_token = ft_strdup(temp);
		free(temp);
		i++;
	}
	free(trimmed_token);
	ft_strarr_clear(chanks);
	return (expanded_token);
}
