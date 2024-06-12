/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:45:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/12 11:43:41 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Prints an error to the Standard Error.
/// @param env The minishell environment, to get the shell name.
/// @param path The command or path used to cause an error.
/// @param error The error message to display.
/// @return 
static int	error(t_environment *env, const char *path, const char *error)
{
	ft_putstr_fd((char *) env->shell, STDERR_FILENO);
	ft_putstr_fd(": export: \'", STDERR_FILENO);
	ft_putstr_fd((char *) path, STDERR_FILENO);
	ft_putstr_fd("\': ", STDERR_FILENO);
	ft_putendl_fd((char *) error, STDERR_FILENO);
	return (EXIT_FAILURE);
}

/// @brief Determines if a key is valid: only contains letters, numbers, and 
/// underscore. Cannot start with a number.
/// @param str The key to check.
/// @return 1 if valid, 0 otherwise.
int	valid_identifier(char *str)
{
	int	end;
	int	index;

	if (!str || ft_isdigit(*str))
		return (FALSE);
	end = ft_strfind(str, "=");
	if (end == -1)
		end = ft_strlen(str);
	index = 0;
	if (ft_isdigit(str[index]))
		return (FALSE);
	while (index < end)
	{
		if (!ft_isalnum(str[index]) && str[index] != '_')
			return (FALSE);
		index++;
	}
	return (TRUE);
}

/// @brief Prints all exports from the minishell environment when export is
/// called without arguments.
/// @param env The minishell environment.
/// @return Exit status (EXIT_SUCCESS if success).
static int	export_noargs(t_environment *env)
{
	int		index;
	char	*value;
	int		count;

	index = 0;
	while (index < env->size)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		value = ft_strchr(env->envp[index], '=');
		if (value)
		{
			count = 0;
			while (env->envp[index][count] != '=')
				count += 1;
			write(STDOUT_FILENO, env->envp[index], count);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value + 1, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(env->envp[index], STDOUT_FILENO);
		index++;
	}
	return (EXIT_SUCCESS);
}

/// @brief Processes an argument, adding it to env appropriately based on if it
/// has a key and/or a value.
/// @param arg The argument string to process.
/// @param env The minishell environment.
/// @return Exit code: EXIT_SUCCESS, or EXIT_NO_MEMORY if malloc error
static int	process_arg(char *arg, int index, t_environment *env)
{
	char	*key;
	char	*value;

	if (index != -1)
		key = ft_substr(arg, 0, index);
	else
		key = ft_strdup(arg);
	if (!key)
		return (EXIT_NO_MEMORY);
	value = ft_strchr(arg, '=');
	if (value)
		set_var(env, key, value + 1);
	else
		set_var(env, key, NULL);
	free(key);
	return (EXIT_SUCCESS);
}

/// @brief Builtin: Adds/sets the value of a key/value pair in the form of
/// ``key=value`` to the minishell environment
/// @param env The minishell environment.
/// @param key_value The key/value pair to add/set in the environment.
/// @return Exit code:
/// 0 on success. 1 if set_var failed.  2 if malloc failed.
int	builtin_export(t_command command, t_environment *env)
{
	int		exit_code;
	char	**cmd;
	int		index;

	exit_code = EXIT_SUCCESS;
	if (ft_strarr_len(command.command) == 1)
		return (export_noargs(env));
	cmd = &(command.command[1]);
	while (*cmd)
	{
		index = ft_strfind(*cmd, "=");
		if (valid_identifier(*cmd))
		{
			if (process_arg(*cmd, index, env) == EXIT_NO_MEMORY)
				return (EXIT_NO_MEMORY);
		}
		else
			exit_code = error(env, *cmd, "not a valid identifier");
		cmd++;
	}
	return (exit_code);
}
