/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:08:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/27 23:55:45 by jhughes          ###   ########.fr       */
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

/// @brief Exits the shell with the exit code of that last foreground process.
/// @param env The minishell environment.
/// @return Exit status.
int	builtin_exit(t_command *command, t_environment *env)
{
	int	argc;
	int	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (env->echoctl_was_enabled)
		sig_echo_enable();
	else
		sig_echo_disable();
	if (command)
	{
		argc = ft_strarr_len(command->command);
		if (argc > 1)
		{
			if (!is_numeric(command->command[1]))
			{
				ft_printf("%s: exit: %s: numeric argument required\n",
					env->shell, command->command[1]);
				exit_code = 2;
			}
			else if (argc > 2)
			{
				ft_printf("%s: exit: too many arguments\n");
				// Do I need to set env here?
				return (EXIT_FAILURE);
			}
			else
				exit_code = ft_atoi(command->command[1]) % 256;
		}
		else
			exit_code = env->exit_code;
	}
	ft_strarr_clear(env->envp);
	ft_strarr_clear(command->command);
	exit(exit_code);
	return (exit_code);
}
