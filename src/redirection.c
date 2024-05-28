/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <hiono@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:28:43 by hiono             #+#    #+#             */
/*   Updated: 2024/05/28 17:44:40 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief child process takes input from terminal until it hits the EOF string
/// and passes it to the pipe so that command can take it as input
/// @param pipefd_c the pipe to pass the input of heredoc
/// @param command t_command structure which includs the EOF string
void	heredoc_in(int pipefd_c[2], t_command command)
{
	int		pid;
	char	*line;
	char	*input;

	pid = fork();
	if (pid < -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		input = NULL;
		while (TRUE)
		{
			line = readline("\e[1;34mhere_doc> \e[0m");
			if (!ft_strncmp(line, command.heredoc_eof, ft_strlen(line) + 1))
				break ;
			if (!input)
				input = ft_strjoin(line, "\n");
			else
				input = ft_strconcat(input, line, "\n", NULL);
		}
		ft_putstr_fd(input, pipefd_c[1]);
		exit(EXIT_SUCCESS);
	}
	else if (0 < pid)
		dup2(pipefd_c[0], STDIN_FILENO);
}

/// @brief sets the stdin file descripter correspoinding to the redirection.
/// If it has a child process, it's set as a pipe from the child process.
/// @param pipefd_c pipe passed to child process.
/// The command will take input from the pipe
/// @param command t_command structure to be execute
/// @param index 
void	dup_in_fds(int pipefd_c[2], t_command command, int index,
		t_environment *env)
{
	int		in_fd;

	if (0 < index)
		dup2(pipefd_c[0], STDIN_FILENO);
	else if (command.in_redirection == SINGLE_IN)
	{
		if (access(command.in_file, F_OK))
		{
			errprint("%s: No such file or directory\n", command.in_file, env);
			exit(EXIT_FAILURE);
		}
		else if (access(command.in_file, R_OK))
		{
			errprint("%s: Permission denied\n", command.in_file, env);
			exit(EXIT_FAILURE);
		}
		in_fd = open(command.in_file, O_RDONLY);
		if (in_fd < 0)
			exit(EXIT_FAILURE);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (command.in_redirection == DOUBLE_IN)
		heredoc_in(pipefd_c, command);
	close(pipefd_c[1]);
}

/// @brief sets the stdout file descripter correspoinding to the redirection.
/// If no redirections, it's set as a pipe to the parent process.
/// @param pipefd_p pipe passed from parent process.
/// The command will pass the result to the pipe
/// @param command t_command structure to be execute
void	dup_out_fds(int pipefd_p[2], t_command command, t_environment *env)
{
	int		out_fd;

	if (pipefd_p)
	{
		close(pipefd_p[0]);
		dup2(pipefd_p[1], STDOUT_FILENO);
		return ;
	}
	if (command.out_redirection == NONE)
		return ;
	if (!access(command.out_file, F_OK) && access(command.out_file, W_OK))
	{
		errprint("%s: Permission denied\n", command.out_file, env);
		exit(EXIT_FAILURE);
	}
	out_fd = STDOUT_FILENO;
	if (command.out_redirection == SINGLE_OUT)
		out_fd = open(command.out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (command.out_redirection == DOUBLE_OUT)
		out_fd = open(command.out_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
		exit(EXIT_FAILURE);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}
