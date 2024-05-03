/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:37:06 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/03 13:46:15 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_key(char **env, char *key)
{
	const	int	size = ft_strarrlen(env);
	int			index;
	
	while (index < size)
	{
		if (ft_strncmp(env[index], key, ft_strlen(key)) == 0
			&& ft_strchr(env[index], '=') == env[index] + ft_strlen(key))
				return (env[index]);
		else
			index++;
	}
	return (NULL);
}

const char	*get_value(char **env, char *key)
{
	char	*var;

	var = get_key(env, key);
	if (var)
		return (ft_strchr(var, '=') + 1);
	return (NULL);
}

char	*add_var(char **env, char *key, char *value)
{
	const int	size = ft_strarrlen(env);
	char		*var;

	var = ft_strconcat(key, "=", value, NULL);
	if (!var)
		// Handle Error
	env[size] = env[size - 1];
	env[size - 1] = var;
	// Resize if necessary
}

char	*set_var(char **env, char *key, char *value)
{
	
}

char	*remove_var(char **env, char *key)
{
	const	int	size = ft_strarrlen(env);
	int			index;

	index = 0;
	while (index < size)
	{
		if (ft_strncmp(env[index], key, ft_strlen(key)) == 0
			&& ft_strchr(env[index], '=') == env[index] + ft_strlen(key))
		{
			free(env[index]);
			while (index < size)
			{
				env[index] = env[index + 1];
				// Make sure that this works at full array.
				index++;
			}
			env[index] = NULL;
		}
		else
			index++;
	}
	return (NULL);
}
