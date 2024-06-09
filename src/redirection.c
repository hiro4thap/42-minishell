/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:28:43 by hiono             #+#    #+#             */
/*   Updated: 2024/06/09 18:22:19 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief A child process that handles reading input for heredoc, piping it to
/// the parent's STDIN.
/// @param command t_command structure which includs the EOF string
/// @param heredoc_pipe The pipe to pass output through.
static void	heredoc_readinput(t_command command, int heredoc_pipe[2])
{
	char	*line;
	char	*input;

	close(heredoc_pipe[PIPE_READ]);
	input = NULL;
	while (TRUE)
	{
		line = readline("\001\e[1;32m\002here_doc> \001\e[0m\002");
		if (!ft_strncmp(line, command.heredoc_eof, ft_strlen(line) + 1))
			break ;
		if (!input)
			input = ft_strjoin(line, "\n");
		else
			input = ft_strconcat(input, line, "\n", NULL);
	}
	ft_putstr_fd(input, heredoc_pipe[PIPE_WRITE]);
	close(heredoc_pipe[PIPE_WRITE]);
	exit(EXIT_SUCCESS);
}

/// @brief child process takes input from terminal until it hits the EOF string
/// and passes it to the pipe so that command can take it as input
/// @param command t_command structure which includs the EOF string
static void	heredoc_in(t_command command)
{
	int		heredoc_pipe[2];
	int		pid;

	if (pipe(heredoc_pipe) == -1)
		return ;
	pid = fork();
	if (pid < -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		heredoc_readinput(command, heredoc_pipe);
	else if (0 < pid)
	{
		close(heredoc_pipe[PIPE_WRITE]);
		dup2(heredoc_pipe[PIPE_READ], STDIN_FILENO);
		close(heredoc_pipe[PIPE_READ]);
		while (wait(0) > 0)
			continue ;
	}
}

/// @brief sets the stdin file descripter correspoinding to the redirection.
/// If it has a child process, it's set as a pipe from the child process.
/// @param pipefd_c pipe passed to child process.
/// The command will take input from the pipe
/// @param command t_command structure to be execute
/// @param index 
void	dup_in_fds(int pipe_in[2], t_command command, int index,
		t_environment *env)
{
	int		in_fd;

	if (0 < index)
	{
		dup2(pipe_in[PIPE_READ], STDIN_FILENO);
		close(pipe_in[PIPE_READ]);
		return ;
	}
	else if (command.in_redirection == SINGLE_IN)
	{
		if (access(command.in_file, F_OK))
			errprint_exit("%s: No such file or directory\n", command.in_file,
				env, EXIT_FAILURE);
		else if (access(command.in_file, R_OK))
			errprint_exit("%s: Permission denied\n", command.in_file,
				env, EXIT_FAILURE);
		in_fd = open(command.in_file, O_RDONLY);
		if (in_fd < 0)
			exit(EXIT_FAILURE);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (command.in_redirection == DOUBLE_IN)
		heredoc_in(command);
}

/// @brief sets the stdout file descripter correspoinding to the redirection.
/// If no redirections, it's set as a pipe to the parent process.
/// @param pipefd_p pipe passed from parent process.
/// The command will pass the result to the pipe
/// @param command t_command structure to be execute
void	dup_out_fds(int pipe_out[2], t_command command, t_environment *env)
{
	int		out_fd;

	if (pipe_out)
	{
		close(pipe_out[PIPE_READ]);
		dup2(pipe_out[PIPE_WRITE], STDOUT_FILENO);
		close(pipe_out[PIPE_WRITE]);
		return ;
	}
	if (command.out_redirection == NONE)
		return ;
	if (!access(command.out_file, F_OK) && access(command.out_file, W_OK))
		errprint_exit("%s: Permission denied\n", command.out_file,
			env, EXIT_FAILURE);
	out_fd = STDOUT_FILENO;
	if (command.out_redirection == SINGLE_OUT)
		out_fd = open(command.out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (command.out_redirection == DOUBLE_OUT)
		out_fd = open(command.out_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (out_fd < 0)
		errprint_exit("%s: No such file or directory\n", command.out_file,
			env, EXIT_FAILURE);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}
