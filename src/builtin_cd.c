/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:46:37 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/13 12:34:43 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Changes the current working directory based on ``path``.
/// @param env The minishell environment.
/// @param path The path. Can be absolute (defined from root), or relative
/// (to current directory).
/// @return Exit Code: 0 on success, 1 otherwise.
int	builtin_cd(t_environment *env, char *path)
{
	// Check if absolute (starts with /) or relative (should match file, including . or ..)
	// Generate absolute path if ``path`` is relative path.
	// Validate absolute path for existence and accessibility.
	// If valid, updated current directory, else return appropriate error.
	
	// cd with no args should try to access $HOME.
	// ft_putendl_fd("minishell: cd: HOME not set");
	if (path && !(*path))
	{
		const char *home = get_value(env, "HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
		if (chdir(home) != 0)
		{
			perror("minishell: cd");
		}
		return (0);
	}
	(void) env;
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
	}
	return (0);
}