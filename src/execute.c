/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/06/01 16:33:35 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	run_file(t_command command, t_environment *envp)
{
	char	*path;
	char	**dirs;
	char	*cmd;
	int		i;

	if (get_value(envp, "PATH"))
		path = ft_strdup(get_value(envp, "PATH"));
	else
		path = getcwd(NULL, 0);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strconcat(dirs[i], "/", command.command[0], NULL);
		execve(cmd, command.command, envp->envp);
		free(cmd);
		i++;
	}
	free(path);
	ft_strarr_clear(dirs);
}

/// @brief searching executable file in PATH directories before execution.
/// If file is not found, a message will be displayed
/// @param command t_command structure to be execute
/// @param envp environment variable
void	execute_simple_command(t_command command, t_environment *envp)
{
	char	*cmd;
	char	*pwd;

	if (!command.command[0])
		exit(EXIT_SUCCESS);
	if (command.command[0][0] == '.')
	{
		pwd = getcwd(NULL, 0);
		cmd = ft_strconcat(pwd, "/", command.command[0], NULL);
		execve(cmd, command.command, envp->envp);
		free(cmd);
		free(pwd);
	}
	else if (command.command[0][0] == '/')
		execve(command.command[0], command.command, envp->envp);
	else if (is_builtin(command))
		exit(run_builtin(command, envp));
	else
		run_file(command, envp);
	errprint("%s: command not found\n", command.command[0], envp);
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
		dup_in_fds(pipefd_c, command, index, envp);
		dup_out_fds(pipefd_p, command, envp);
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
void	commands(char *input, t_environment *env)
{
	char	**commands;
	int		arrlen;
	int		pid;
	int		status;

	commands = split_command(input);
	arrlen = ft_strarr_len(commands);
	if ((arrlen == 1 && !process_builtins(commands, env)) || arrlen > 1)
	{
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_commands(commands, NULL, arrlen - 1, env);
		if (0 < pid)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				env->exit_code = WEXITSTATUS(status);
		}
	}
	ft_strarr_clear(commands);
}
