/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/05/08 19:31:13 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// 1) split input by '|' into commands (delimeters can be || or && in bonus)
// 2) if < exists, set fd as input
// 3) if << exists, read till limiter
// 4) if > exists, set fd as output (overwrite)
// 5) if >> exists, set fd as output (append)

char	**get_envp_path(char **envp) //TODO:remove after implementing get_env_var
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

void	dup_in_fds(int pipefd_c[2], t_command command)
{
	int	in_fd;

	if (pipefd_c)
	{
		dup2(pipefd_c[0], STDIN_FILENO);
		return ;
	}
	if (command.in_redirection == NONE)
		return ;
	else if (command.in_redirection == SINGLE_IN)
	{
		if (access(command.in_file, F_OK))
		{
			ft_printf("no such file or directory: %s\n", command.in_file);
			exit(EXIT_FAILURE);
		}
		else if (access(command.in_file, R_OK))
		{
			ft_printf("permission denied: %s\n", command.in_file);
			exit(EXIT_FAILURE);
		}
		in_fd = open(command.in_file, O_RDONLY);
		if (in_fd < 0)
			exit(EXIT_FAILURE);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (command.in_redirection == DOUBLE_IN)
		return ; //TODO:implement heredoc
}

void	dup_out_fds(int pipefd_p[2], t_command command)
{
	int		out_fd;

	close(pipefd_p[0]);
	if (command.out_redirection == NONE)
	{
		dup2(pipefd_p[1], STDOUT_FILENO);
		return ;
	}
	if (!access(command.out_file, F_OK) && access(command.out_file, W_OK))
	{
		ft_printf("permission denied: %s\n", command.out_file);
		exit(EXIT_FAILURE);
	}
	out_fd = STDOUT_FILENO;
	if (command.out_redirection == SINGLE_OUT)
		out_fd = open(command.out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (command.out_redirection == DOUBLE_OUT)
		out_fd = open(command.out_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
		exit(EXIT_FAILURE);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

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
	ft_printf("command not found: %s\n", command.command[0]);
	ft_strclear(command.command);
	ft_strclear(dirs); //TODO:needs to check if get_value allocates memory
	exit(127);
}

/// @brief depending on the 
/// @param commands whole array of command 
/// @param pipefd_p pipe passed from parent process
/// @param index index for the command to execute
/// @param envp TODO:should be replaced by get_value functions
void	execute_commands(char **commands, int pipefd_p[2], int index, char **envp)
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
		dup_in_fds(pipefd_c, command);
		dup_out_fds(pipefd_p, command);
		execute_simple_command(command, envp);
	}
	else if (pid == 0 && 0 < index)
		execute_commands(commands, pipefd_c, --index, envp);
	else if (pid == 0 && index == 0)
		exit(EXIT_SUCCESS);
}

void	execute_command(char *commands, int pipefd_c[2], char **envp)
{
	t_command	command;

	(void) pipefd_c;
	command = split_cmd(commands);
	dup_in_fds(NULL, command);
	dup_out_fds(pipefd_c, command);
	execute_simple_command(command, envp);
}

size_t	ft_arrlen(char **str_array)
{
	size_t	len;

	len = 0;
	while (*str_array)
	{
		len += 1;
		str_array++;
	}
	return (len);
}

/// @brief split the whole command into chanks by pipelines before execution
/// @param input the string input through prompt
/// @param envp TODO:should be replaced by get_value functions
/// @return void
void	commands(char *input, char **envp)
{
	char	**commands;
	int		arrlen;
	int		pipefd_c[2];
	int		pid;
	char	*buffer = malloc(1000);

	commands = ft_split(input, '|');
	arrlen = ft_arrlen(commands);
	if (arrlen == 1)
	{
		if (pipe(pipefd_c) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_command(commands[0], pipefd_c, envp);
		else if (0 < pid)
		{
			close(pipefd_c[1]);
			read(pipefd_c[0], buffer, 1000);  //TODO:find a better way to connect pipecd_c[0] to STDOUT
			ft_printf("%s", buffer);
			free(buffer);
			close(pipefd_c[0]);
		}
	}	
	else if (1 < arrlen)
	{
		if (pipe(pipefd_c) == -1)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_commands(commands, pipefd_c, arrlen - 1, envp);
		else if (0 < pid)
		{
			close(pipefd_c[1]);
			read(pipefd_c[0], buffer, 1000);  //TODO:find a better way to connect pipecd_c[0] to STDOUT
			ft_printf("%s", buffer);
			free(buffer);
			close(pipefd_c[0]);
		}
	}
	ft_strclear(commands);
}

