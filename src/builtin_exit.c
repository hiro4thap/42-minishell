/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:08:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/06/12 09:45:39 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static int	exit_args(int argc, t_command *command, t_environment *env,
					int *exit_code)
{
	if (!is_numeric(command->command[1]))
	{
		ft_putstr_fd((char *) env->shell, STDERR_FILENO);
		ft_putstr_fd(": exit: ", STDERR_FILENO);
		ft_putstr_fd(command->command[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		*exit_code = EXIT_OUT_OF_RANGE;
	}
	else if (argc > 2)
	{
		ft_putstr_fd((char *) env->shell, STDERR_FILENO);
		ft_putendl_fd(": exit: too many arguments", STDERR_FILENO);
		*exit_code = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	else
		*exit_code = ft_atoi(command->command[1]) % 256;
	return (EXIT_SUCCESS);
}

/// @brief Exits the shell with the exit code of that last foreground process.
/// @param env The minishell environment.
/// @return Exit status.
int	builtin_exit(t_command *command, t_environment *env)
{
	int	argc;
	int	exit_code;

	exit_code = env->exit_code;
	if (command)
	{
		argc = ft_strarr_len(command->command);
		if (argc > 1
			&& (exit_args(argc, command, env, &exit_code) == EXIT_FAILURE))
			return (exit_code);
	}
	else
		ft_putendl_fd("exit", STDERR_FILENO);
	tcsetattr(0, 0, &env->init_state);
	ft_strarr_clear(env->envp);
	if (command)
		ft_strarr_clear(command->command);
	exit(exit_code);
	return (exit_code);
}
