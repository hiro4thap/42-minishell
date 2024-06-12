/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_chank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:26:00 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 13:41:19 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static int	handle_simple_dollar(char *var, char **dollar)
{
	if (!ft_strncmp(var, "$", 2))
	{
		free(var);
		*dollar = ft_strchr(*dollar + 1, '$');
		return (TRUE);
	}
	return (FALSE);
}

static char	*get_var(char *dollar)
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

//[MALLOC]
static char	*expand_var(char *expanded, char *var, t_environment *env)
{
	char	*value;
	char	*temp;

	if (!ft_strncmp(var, "$?", 3))
		value = ft_itoa(env->exit_code);
	else if (ft_strncmp(var, "$", 2) && get_value(env, var + 1))
		value = ft_strdup(get_value(env, var + 1));
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	temp = replace_substr(expanded, var, value);
	free(value);
	free(expanded);
	return (temp);
}

//[MALLOC]
char	*expand_chank(char *chank, t_environment *env)
{
	char	*expanded;
	char	*dollar;
	char	*var;

	expanded = ft_strdup(chank);
	if (!expanded)
		return (free_vars(chank, NULL, NULL));
	dollar = ft_strchr(chank, '$');
	while (dollar)
	{
		var = get_var(dollar);
		if (!var)
			return (free_vars(chank, expanded, NULL));
		if (handle_simple_dollar(var, &dollar))
			continue ;
		expanded = expand_var(expanded, var, env);
		free(var);
		if (!expanded)
			return (free_vars(chank, NULL, NULL));
		dollar = ft_strchr(dollar + 1, '$');
	}
	free(chank);
	return (expanded);
}
