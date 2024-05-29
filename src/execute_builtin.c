/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:27:47 by hiono             #+#    #+#             */
/*   Updated: 2024/05/29 13:47:59 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_command command)
{
	if (ft_strncmp(command.command[0], "cd", 3) == 0
		|| ft_strncmp(command.command[0], "echo", 5) == 0
		|| ft_strncmp(command.command[0], "env", 4) == 0
		|| ft_strncmp(command.command[0], "exit", 5) == 0
		|| ft_strncmp(command.command[0], "export", 7) == 0
		|| ft_strncmp(command.command[0], "pwd", 4) == 0
		|| ft_strncmp(command.command[0], "unset", 6) == 0)
		return (TRUE);
	return (FALSE);
}

int	run_builtin(t_command command, t_environment *env)
{
	int	exit_code;

	exit_code = EXIT_COMMAND_NOT_EXIST;
	if (!ft_strncmp(command.command[0], "echo", 5))
		exit_code = builtin_echo(ft_strarr_len(command.command),
				command.command, env);
	else if (!ft_strncmp(command.command[0], "cd", 3))
		exit_code = builtin_cd(command, env);
	else if (!ft_strncmp(command.command[0], "pwd", 4))
		exit_code = builtin_pwd(env);
	else if (!ft_strncmp(command.command[0], "export", 7))
		exit_code = builtin_export(command, env);
	else if (!ft_strncmp(command.command[0], "unset", 6))
		exit_code = builtin_unset(command, env);
	else if (!ft_strncmp(command.command[0], "env", 4))
		exit_code = builtin_env(env);
	else if (!ft_strncmp(command.command[0], "exit", 5))
		exit_code = builtin_exit(&command, env);
	return (exit_code);
}

int	process_builtins(char **commands, t_environment *env)
{
	t_command	cmd;

	cmd = parse_command(*commands, env);
	if (ft_strncmp(cmd.command[0], "exit", 5) == 0)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		env->exit_code = builtin_exit(&cmd, env);
		ft_strarr_clear(cmd.command);
		return (TRUE);
	}
	else if (ft_strncmp(cmd.command[0], "export", 7) == 0
		|| ft_strncmp(cmd.command[0], "unset", 6) == 0
		|| ft_strncmp(cmd.command[0], "cd", 3) == 0)
	{
		env->exit_code = run_builtin(cmd, env);
		ft_strarr_clear(cmd.command);
		return (TRUE);
	}
	ft_strarr_clear(cmd.command);
	return (FALSE);
}
