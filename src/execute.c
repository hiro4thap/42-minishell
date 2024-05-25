/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/05/25 23:14:53 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief TODO:remove after implementing get_env_var
char	**get_envp_path(char **envp)
{
	char	*envp_path_str;
	char	**envp_path;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			envp_path_str = *envp + 5;
		envp++;
	}
	envp_path = ft_split(envp_path_str, ':');
	return (envp_path);
}

void	delete_command(t_command command)
{
	ft_strarr_clear(command.command);
}

bool	is_builtin(t_command command)
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

int	run_builtin(t_command command, t_environment *envp)
{
	int	exit_code;

	exit_code = EXIT_COMMAND_NOT_EXIST;
	if (!ft_strncmp(command.command[0], "echo", 5))
		exit_code = builtin_echo(ft_strarr_len(command.command),
				command.command, envp);
	else if (!ft_strncmp(command.command[0], "cd", 3))
		exit_code = builtin_cd(command, envp);
	else if (!ft_strncmp(command.command[0], "pwd", 4))
		exit_code = builtin_pwd(envp);
	else if (!ft_strncmp(command.command[0], "export", 7))
		exit_code = builtin_export(command, envp);
	else if (!ft_strncmp(command.command[0], "unset", 6))
		exit_code = builtin_unset(command, envp);
	else if (!ft_strncmp(command.command[0], "env", 4))
		exit_code = builtin_env(envp);
	else if (!ft_strncmp(command.command[0], "exit", 5))
		exit_code = EXIT_SUCCESS;
	delete_command(command);
	return (exit_code);
}

/// @brief searching executable file in PATH directories before execution.
/// If file is not found, a message will be displayed
/// @param command t_command structure to be execute
/// @param envp TODO:should be replaced by get_value functions
void	execute_simple_command(t_command command, t_environment *envp)
{
	char	**dirs;
	int		i;
	char	*cmd;

	if (is_builtin(command))
		exit(run_builtin(command, envp));
	else
	{
		dirs = get_envp_path(envp->envp); //TODO:get_value from env vars
		i = 0;
		while (dirs[i])
		{
			cmd = ft_strconcat(dirs[i], "/", command.command[0], NULL);
			execve(cmd, command.command, envp->envp);
			free(cmd);
			i++;
		}
		errprint("command not found: %s\n", command.command[0]);
		ft_strarr_clear(dirs); //TODO:needs to check if get_value allocates memory
		delete_command(command);
		exit(EXIT_COMMAND_NOT_EXIST);
	}
}

/// @brief parent process handles file descripter and exectue simple command
/// child process recursively execute itself unless it's the first command
/// @param commands whole array of simple commands
/// @param pipefd_p pipe passed from parent process.
/// The function will pass the result of executing command to the pipe
/// @param index index for the simple command to execute
/// @param envp TODO:should be replaced by get_value functions
void	execute_commands(
		char **commands, int pipefd_p[2], int index, t_environment *envp)
{
	int			pipefd_c[2];
	int			pid;
	t_command	command;

	if (pipe(pipefd_c) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (0 < pid)
	{
		command = parse_command(commands[index]);
		dup_in_fds(pipefd_c, command, index);
		dup_out_fds(pipefd_p, command);
		execute_simple_command(command, envp);
	}
	else if (pid == 0 && 0 < index)
		execute_commands(commands, pipefd_c, index - 1, envp);
	else if (pid == 0 && index == 0)
		exit(EXIT_SUCCESS);
}

int	process_builtins(char **commands, t_environment *env)
{
	t_command	cmd;

	cmd = parse_command(*commands);
	if (ft_strncmp(cmd.command[0], "exit", 5) == 0)
	{
		delete_command(cmd);
		builtin_exit(env);
		return (TRUE);
	}
	else if (ft_strncmp(cmd.command[0], "export", 7) == 0
		|| ft_strncmp(cmd.command[0], "unset", 6) == 0
		|| ft_strncmp(cmd.command[0], "cd", 3) == 0)
	{
		env->exit_code = run_builtin(cmd, env);
		delete_command(cmd);
		return (TRUE);
	}
	delete_command(cmd);
	return (FALSE);
}

/// @brief split the whole command into chanks by pipelines before execution
/// @param input the string input through prompt
/// @param envp TODO:should be replaced by get_value functions
void	commands(char *input, t_environment *env)
{
	char	**commands;
	int		arrlen;
	int		pid;

	commands = ft_split(input, '|');
	arrlen = ft_arrlen(commands);
	if ((arrlen == 1 && !process_builtins(commands, env)) || arrlen > 1)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_commands(commands, NULL, arrlen - 1, env);
		if (0 < pid)
			waitpid(pid, &(env->exit_code), 0);
	}
	ft_strarr_clear(commands);
}
