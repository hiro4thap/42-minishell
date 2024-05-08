/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:37:06 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/08 12:30:31 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Initialises environment from the calling shells environment.
/// @param[out] env Environment pointer to be initialised. 
/// @param[in] shell_env Environment from calling process.
/// @return Exit code: 0 on success, 1 otherwise.
int	init_environment(t_environment **env, char **shell_env)
{
	const int	total_user_variables = 15;

	(*env) = malloc(sizeof(t_environment));
	if (!(*env))
		return (1);
	(*env)->size = ft_strarrlen(shell_env);
	(*env)->max_size = (*env)->size + total_user_variables;
	(*env)->envp = ft_calloc((*env)->max_size, sizeof(char *));
	if (!(*env)->envp)
		return (1);
	return (0);
}

/// @brief Searches the minishell environment for the specified key.
/// @param env The minishell environment.
/// @param key The key being searched for.
/// @return Pointer to key/value pair, or NULL if not found. 
const char	*get_key(t_environment *env, char *key)
{
	int	index;

	index = 0;
	while (index < env->size)
	{
		if (ft_strncmp(env->envp[index], key, ft_strlen(key)) == 0
			&& ft_strchr(env->envp[index], '=') == env->envp[index]
			+ ft_strlen(key))
			return (env->envp[index]);
		else
			index++;
	}
	return (NULL);
}

/// @brief Searches the minishell environment for the specified key.
/// @param env The minishell environment.
/// @param key The key being searched for.
/// @return Position index of key in minishell environment array.
int	get_key_index(t_environment *env, char *key)
{
	int	index;

	index = 0;
	while (index < env->size)
	{
		if (ft_strncmp(env->envp[index], key, ft_strlen(key)) == 0
			&& ft_strchr(env->envp[index], '=') == env->envp[index]
			+ ft_strlen(key))
			return (index);
		else
			index++;
	}
	return (-1);
}

/// @brief Adds a new key/value pair to the minishell environment.
/// Resizes the environment variable if necessary. 
/// @param env The minishell environment.
/// @param key The key to be added.
/// @param value The value to set with the new key.
/// @return Exit code: 0 on success, 1 otherwise.
int	add_var(t_environment *env, char *key, char *value)
{
	const int	size = ft_strarrlen(env->envp);
	char		*var;
	char		*temp_array;

	var = ft_strconcat(key, "=", value, NULL);
	if (!var)
	{
		// Handle Error
	}
	if (env->size == env->max_size)
	{
		temp_array = ft_strarr_resize(env->envp, env->size + 10);
		if (!temp_array)
		{
			// Handle Error
		}
		env->envp = temp_array;
		env->max_size += 10;
	}
	env->envp[env->size] = env->envp[env->size - 1];
	env->envp[size - 1] = var;
	env->size += 1;
}

/// @brief Sets value of a key, adding it to the environment if not already
///	present.
/// @param env The minishell environment.
/// @param key The key to be set.
/// @param value The value to set in the key.
/// @return Exit code: 0 on success, 1 otherwise.
int	set_var(t_environment *env, char *key, char *value)
{
	char	*var;
	int		index;

	index = get_key_index(env, key);
	if (index == -1)
		return (add_var(env, key, value));
	var = ft_strconcat(key, "=", value, NULL);
	if (!var)
	{
		// Handle Error
	}
	free(env->envp[index]);
	env->envp[index] = var;
	return (0);
}

/// @brief Removes key from the minishell environment if it exists.
/// @param env The minishell environment.
/// @param key The key to be removed.
/// @return Exit code: 0 on success, 1 otherwise.
int	remove_var(t_environment *env, char *key)
{
	int	index;

	index = 0;
	while (index < env->size)
	{
		if (ft_strncmp(env->envp[index], key, ft_strlen(key)) == 0
			&& ft_strchr(env->envp[index], '=') == env->envp[index]
			+ ft_strlen(key))
		{
			free(env->envp[index]);
			while (index < env->size)
			{
				env->envp[index] = env->envp[index + 1];
				// Make sure that this works at full array.
				index++;
			}
			env->envp[index] = NULL;
		}
		else
			index++;
	}
	return (0);
}

/// @brief Gets the value of the key in the minishell environment, if present.
/// @param env The minishell environment.
/// @param key The key to find the value of.
/// @return Pointer to start of the value. 
const char	*get_value(t_environment *env, char *key)
{
	int	index;

	index = get_key_index(env, key);
	if (index != -1)
		return (ft_strchr(env->envp[index], '=') + 1);
	return (NULL);
}
