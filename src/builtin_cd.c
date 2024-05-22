/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:46:37 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/22 21:08:32 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	error(char *error_string, char *path)
{
	char *str;

	if (!path)
	{
		perror(error_string);
	}
	else
	{
		str = ft_strjoin(error_string, path);
		perror(str);
		free(str);
	}
}

/// @brief Changes the current working directory based on ``path``.
/// @param env The minishell environment.
/// @param path The path. Can be absolute (defined from root), or relative
/// (to current directory).
/// @return Exit Code: 0 on success, 1 otherwise.
int	builtin_cd(t_command command, t_environment *env)
{
	// Check if absolute (starts with /) or relative (should match file, including . or ..)
	// Generate absolute path if ``path`` is relative path.
	// Validate absolute path for existence and accessibility.
	// If valid, updated current directory, else return appropriate error.
	
	// cd with no args should try to access $HOME.
	// ft_putendl_fd("minishell: cd: HOME not set");

	// At least when home is set to an invalid path, it should include the path
	// after cd: like "cd: hello: invalid path"
	int	argc;

	argc = ft_strarr_len(command.command);
	if (argc > 2)
		error("minishell: cd: too many arguments", NULL);
	if (argc == 1)
	{
		const char *home = get_value(env, "HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
		if (chdir(home) != 0)
		{
			error("minishell: cd: ", NULL);
		}
		return (0);
	}
	(void) env;
	if (chdir(command.command[1]) != 0)
	{
		error("minishell: cd: ", command.command[1]);
	}
	return (0);
}