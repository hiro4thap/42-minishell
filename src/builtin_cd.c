/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:46:37 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/25 16:05:00 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Prints an error to the Standard Error, utilising the error number 
/// strings where applicable.
/// @param env The minishell environment, to get the shell name.
/// @param path The command or path used to cause an error.
/// @param error The error message to display. If NULL, strerror is used.
/// @return 
static int	error(t_environment *env, const char *path, const char *error)
{
	char	*message;

	message = ft_strconcat((char *) env->shell, ": cd: ", path, NULL);
	if (!message)
	{
		perror("minishell: cd");
		exit(EXIT_FAILURE);
	}
	if (!error)
		perror(message);
	else
	{
		message = ft_strjoin(message, error);
		ft_putendl_fd(message, STDERR_FILENO);
	}
	free(message);
	return (EXIT_FAILURE);
}

/// @brief After a sucessful cd, updated PWD in environment vars if set.
/// @param env THe minishell environment.
/// @return Exit code: 0 on success, 1 otherwise.
static int	update_pwd(t_environment *env)
{
	int		index;
	char	*path;
	int		exit_code;

	index = get_key_index(env, "PWD");
	if (index != -1)
	{
		path = getcwd(NULL, 0);
		exit_code = set_var(env, "PWD", path);
		free(path);
	}
	return (exit_code);
}

/// @brief Changes the current working directory based on ``path``.
/// @param env The minishell environment.
/// @param path The path. Can be absolute (defined from root), or relative
/// (to current directory).
/// @return Exit Code: 0 on success, 1 otherwise.
int	builtin_cd(t_command command, t_environment *env)
{
	const int	argc = ft_strarr_len(command.command);
	const char	*home = get_value(env, "HOME");

	if (argc > 2)
		return (error(env, NULL, "too many arguments"));
	if (argc == 1)
	{
		if (!home)
			return (error(env, NULL, "HOME not set"));
		if (chdir(home) != 0)
			return (error(env, home, NULL));
		update_pwd(env);
		return (EXIT_SUCCESS);
	}
	if (chdir(command.command[1]) != 0)
		return (error(env, command.command[1], NULL));
	update_pwd(env);
	return (EXIT_SUCCESS);
}
