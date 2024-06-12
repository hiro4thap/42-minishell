/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:46:37 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/12 10:56:42 by hiono            ###   ########.fr       */
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
		return (EXIT_NO_MEMORY);
	}
	if (!error)
		perror(message);
	else
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putendl_fd((char *) error, STDERR_FILENO);
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

	exit_code = EXIT_SUCCESS;
	index = get_key_index(env, "PWD");
	if (index != -1)
	{
		path = getcwd(NULL, 0);
		exit_code = set_var(env, "PWD", path);
		free(path);
	}
	return (exit_code);
}

/// @brief Handles ~ used in cd commands. Remove if ~ expansion is added.
/// @param command 
/// @param env 
/// @return Exit code of chdir.
static int	change_home(t_command *command, t_environment *env)
{
	int		exit_code;
	char	*path;

	path = ft_strconcat((char *) env->home, &command->command[1][1], NULL);
	if (!path)
		return (EXIT_NO_MEMORY);
	if (chdir(path) != 0)
	{
		exit_code = error(env, path, NULL);
		free(path);
		return (exit_code);
	}
	free(path);
	return (EXIT_SUCCESS);
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
	int			exit_code;

	if (argc > 2)
		return (error(env, NULL, "too many arguments"));
	if (argc == 1)
	{
		if (!home)
			return (error(env, NULL, "HOME not set"));
		if (chdir(home) != 0)
			return (error(env, home, NULL));
		exit_code = update_pwd(env);
		return (exit_code);
	}
	if (env->home && ft_strncmp(command.command[1], "~", 1) == 0)
	{
		exit_code = change_home(&command, env);
		if (exit_code != EXIT_SUCCESS)
			return (exit_code);
	}
	else if (chdir(command.command[1]) != 0)
		return (error(env, command.command[1], NULL));
	exit_code = update_pwd(env);
	return (exit_code);
}
