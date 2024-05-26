/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/05/26 17:08:52 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_builtin(t_command command)
{
	if (ft_strncmp(command.command[0], "cd", 2) == 0
		|| ft_strncmp(command.command[0], "echo", 4) == 0
		|| ft_strncmp(command.command[0], "env", 3) == 0
		|| ft_strncmp(command.command[0], "exit", 4) == 0
		|| ft_strncmp(command.command[0], "export", 6) == 0
		|| ft_strncmp(command.command[0], "pwd", 3) == 0
		|| ft_strncmp(command.command[0], "unset", 5) == 0)
		return (TRUE);
	return (FALSE);
}

int	run_builtin(t_command command, t_environment *envp)
{
	if (!ft_strncmp(command.command[0], "echo", 5))
		return (builtin_echo(ft_strarr_len(command.command),
				command.command, envp));
	else if (!ft_strncmp(command.command[0], "cd", 3))
		return (builtin_cd(command, envp));
	else if (!ft_strncmp(command.command[0], "pwd", 4))
		return (builtin_pwd(envp));
	else if (!ft_strncmp(command.command[0], "export", 7))
		return (builtin_export(command, envp));
	else if (!ft_strncmp(command.command[0], "unset", 6))
		return (builtin_unset(command, envp));
	else if (!ft_strncmp(command.command[0], "env", 4))
		return (builtin_env(envp));
	else if (!ft_strncmp(command.command[0], "exit", 5))
		exit(builtin_exit(envp));
	return (EXIT_COMMAND_NOT_EXIST);
}

/// @brief searching executable file in PATH directories before execution.
/// If file is not found, a message will be displayed
/// @param command t_command structure to be execute
/// @param envp environment variable
void	execute_simple_command(t_command command, t_environment *envp)
{
	char	**dirs;
	int		i;
	char	*cmd;

	char	*pwd = getcwd(NULL, 0);
	dirs = NULL; //TODO: cleared by spliting functions
	cmd = NULL; //TODO: cleared by spliting functions
	if (command.command[0][0] == '.')
	{
		cmd = ft_strconcat(pwd, "/", command.command[0], NULL);
		execve(cmd, command.command, envp->envp);
		free(cmd);
	}
	else if (command.command[0][0] == '/')
		execve(command.command[0], command.command, envp->envp);
	else if (is_builtin(command))
		exit(run_builtin(command, envp));
	else
	{
		const char	*path = get_value(envp, "PATH");
		if (!path || !*path)
		{
			cmd = ft_strconcat(pwd, "/", command.command[0], NULL);
			execve(cmd, command.command, envp->envp);
			free(cmd);
		}
		else
		{
			dirs = ft_split(path, ':');
			i = 0;
			while (dirs[i])
			{
				cmd = ft_strconcat(dirs[i], "/", command.command[0], NULL);
				execve(cmd, command.command, envp->envp);
				free(cmd);
				i++;
			}
			ft_strarr_clear(dirs);
		}
	}
	errprint("command not found: %s\n", command.command[0]);
	ft_strarr_clear(command.command);
	exit(EXIT_COMMAND_NOT_EXIST);
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
		command = parse_command(commands[index], envp);
		dup_in_fds(pipefd_c, command, index);
		dup_out_fds(pipefd_p, command);
		execute_simple_command(command, envp);
	}
	else if (pid == 0 && 0 < index)
		execute_commands(commands, pipefd_c, index - 1, envp);
	else if (pid == 0 && index == 0)
		exit(EXIT_SUCCESS);
}

/// @brief split the whole command into chanks by pipelines before execution
/// @param input the string input through prompt
/// @param envp TODO:should be replaced by get_value functions
void	commands(char *input, t_environment *envp)
{
	char	**commands;
	int		arrlen;
	int		pid;

	commands = ft_split(input, '|');
	arrlen = ft_arrlen(commands);
	if (arrlen == 1)
	{
		// Check for whitespace?
		if (ft_strncmp(*commands, "export", 6) == 0
			|| ft_strncmp(*commands, "unset", 5) == 0
			|| ft_strncmp(*commands, "cd", 2) == 0
			|| ft_strncmp(*commands, "exit", 4) == 0)
		{
			run_builtin(parse_command(*commands, envp), envp);
			ft_strarr_clear(commands);
			return ;
		}
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_commands(commands, NULL, arrlen - 1, envp);
	if (0 < pid)
		waitpid(pid, 0, 0);
	ft_strarr_clear(commands);
}
