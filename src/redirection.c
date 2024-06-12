/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:28:43 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 13:20:22 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Redirects ``std_fd`` to ``new_fd`` then closes ``new_fd``.
/// @param new_fd The file descriptor to use insted of STDIO. 
/// @param std_fd STDOUT_FILENO or STDIN_FILENO.
/// @return EXIT_SUCCESS, or EXIT_DUP_FAILURE if dup2 fails.
static int	redirect_io(int new_fd, int std_fd)
{
	if (dup2(new_fd, std_fd) == -1)
		return (EXIT_DUP_FAILURE);
	close(new_fd);
	return (EXIT_SUCCESS);
}

/// @brief A child process that handles reading input for heredoc, piping it to
/// the parent's STDIN.
/// @param command t_command structure which includs the EOF string
/// @param heredoc_pipe The pipe to pass output through.
static void	heredoc_readinput(t_command command, int heredoc_pipe[2])
{
	char	*line;

	while (TRUE)
	{
		line = readline("\001\e[1;35m\002here_doc >\001\e[0m\002 ");
		if (!ft_strncmp(line, command.heredoc_eof, ft_strlen(line) + 1))
			break ;
		ft_putendl_fd(line, heredoc_pipe[PIPE_WRITE]);
		free(line);
	}
	if (line)
		free(line);
	close(heredoc_pipe[PIPE_WRITE]);
}

/// @brief child process takes input from terminal until it hits the EOF string
/// and passes it to the pipe so that command can take it as input
/// @param command t_command structure which includs the EOF string
static int	heredoc_in(t_command command)
{
	int		heredoc_pipe[2];
	int		pid;

	if (pipe(heredoc_pipe) == -1)
		return (EXIT_PIPE_FAILURE);
	pid = fork();
	if (pid < -1)
		return (EXIT_FORK_FAILURE);
	else if (pid == 0)
	{
		close(heredoc_pipe[PIPE_READ]);
		heredoc_readinput(command, heredoc_pipe);
		close(heredoc_pipe[PIPE_WRITE]);
		exit(EXIT_SUCCESS);
	}
	else if (0 < pid)
	{
		close(heredoc_pipe[PIPE_WRITE]);
		if (dup2(heredoc_pipe[PIPE_READ], STDIN_FILENO) == -1)
			return (EXIT_DUP_FAILURE);
		close(heredoc_pipe[PIPE_READ]);
		while (wait(0) > 0)
			continue ;
	}
	return (EXIT_SUCCESS);
}

/// @brief sets the stdin file descripter correspoinding to the redirection.
/// If it has a child process, it's set as a pipe from the child process.
/// @param pipefd_c pipe passed to child process.
/// The command will take input from the pipe
/// @param command t_command structure to be execute
/// @param index
int	dup_in_fds(int pipe_in[2], t_command command, int index,
		t_environment *env)
{
	int		in_fd;

	if (0 < index)
		return (redirect_io(pipe_in[PIPE_READ], STDIN_FILENO));
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
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (EXIT_DUP_FAILURE);
		close(in_fd);
	}
	else if (command.in_redirection == DOUBLE_IN)
		heredoc_in(command);
	return (EXIT_SUCCESS);
}

/// @brief sets the stdout file descripter correspoinding to the redirection.
/// If no redirections, it's set as a pipe to the parent process.
/// @param pipefd_p pipe passed from parent process.
/// The command will pass the result to the pipe
/// @param command t_command structure to be execute
int	dup_out_fds(int pipe_out[2], t_command command, t_environment *env)
{
	int		out_fd;

	if (pipe_out)
	{
		close(pipe_out[PIPE_READ]);
		return (redirect_io(pipe_out[PIPE_WRITE], STDOUT_FILENO));
	}
	if (command.out_redirection == NONE)
		return (EXIT_SUCCESS);
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
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (EXIT_DUP_FAILURE);
	close(out_fd);
	return (EXIT_SUCCESS);
}
