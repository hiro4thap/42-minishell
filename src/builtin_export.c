/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/13 08:31:02 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Builtin: Adds/sets the value of a key/value pair in the form of
/// ``key=value`` to the minishell environment
/// @param env The minishell environment.
/// @param key_value The key/value pair to add/set in the environment.
/// @return Exit code:
/// 0 on success. 1 if set_var failed.  2 if invalid key. 3 if malloc failed.
int	builtin_export(t_environment *env, char *key_value)
{
	char	*key;
	int		index;
	int		status;

	index = ft_strfind(key_value, "=");
	if (index == -1)
		return (1);
	key = ft_substr(key_value, 0, index);
	if (!key)
		return (2);
	status = set_var(env, key, ft_strchr(key_value, '=') + 1);
	free(key);
	return (status);
}
