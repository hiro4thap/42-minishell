/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:27:47 by hiono             #+#    #+#             */
/*   Updated: 2024/06/11 19:30:17 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_command(t_command *command)
{
	ft_strarr_clear(command->command);
	if (command->in_file)
		free(command->in_file);
	if (command->out_file)
		free(command->out_file);
	if (command->heredoc_eof)
		free(command->heredoc_eof);
}

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
	int			exit_code;

	exit_code = parse_command(0, *commands, env, &cmd);
	if (exit_code)
		return (exit_code);
	if (!cmd.command[0])
	{
		free_command(&cmd);
		return (FALSE);
	}
	if (ft_strncmp(cmd.command[0], "exit", 5) == 0)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		env->exit_code = builtin_exit(&cmd, env);
		free_command(&cmd);
		return (TRUE);
	}
	else if (ft_strncmp(cmd.command[0], "export", 7) == 0
		|| ft_strncmp(cmd.command[0], "unset", 6) == 0
		|| ft_strncmp(cmd.command[0], "cd", 3) == 0)
	{
		env->exit_code = run_builtin(cmd, env);
		free_command(&cmd);
		return (TRUE);
	}
	free_command(&cmd);
	return (FALSE);
}
