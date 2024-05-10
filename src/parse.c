/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/05/10 15:05:05 by hiono            ###   ########.fr       */
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

/// @brief searching executable file in PATH directories before execution.
/// If file is not found, a message will be displayed
/// @param command t_command structure to be execute
/// @param envp TODO:should be replaced by get_value functions
void	execute_simple_command(t_command command, char **envp)
{
	char	**dirs;
	int		i;
	char	*cmd;

	dirs = get_envp_path(envp); //TODO:get_value from env vars
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strconcat(dirs[i], "/", command.command[0], NULL);
		execve(cmd, command.command, envp);
		free(cmd);
		i++;
	}
	errprint("command not found: %s\n", command.command[0]);
	ft_strclear(dirs); //TODO:needs to check if get_value allocates memory
	ft_strclear(command.command);
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
		char **commands, int pipefd_p[2], int index, char **envp)
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
		command = split_cmd(commands[index]);
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
/// @return
void	commands(char *input, char **envp)
{
	char	**commands;
	int		arrlen;
	int		pid;

	commands = ft_split(input, '|');
	arrlen = ft_arrlen(commands);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		execute_commands(commands, NULL, arrlen - 1, envp);
	if (0 < pid)
		waitpid(pid, 0, 0);
	ft_strclear(commands);
}
