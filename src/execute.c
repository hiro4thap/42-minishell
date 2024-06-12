/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 09:17:52 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief searching executable file in PATH directories before execution.
/// If file is not found, a message will be displayed
/// @param command t_command structure to be execute
/// @param envp environment variable
static void	execute_simple_command(t_command command, t_environment *envp)
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

/// @brief Sets up the pipe redirection for the current command, then calls the
/// command.
/// @param command Struct containing all necessary details of current commmand.
/// @param last_command TRUE if last command, FALSE otherwise.
/// @param pipes Pointer to the array of pipes.
/// @param env The minishell environment.
static void	child(t_command command, int last_command, int *pipes,
	t_environment *env)
{
	if (command.id == 0)
		dup_in_fds(NULL, command, command.id, env);
	else
		dup_in_fds(pipes + 2 * (command.id - 1), command, command.id, env);
	if (last_command)
		dup_out_fds(NULL, command, env);
	else
		dup_out_fds(pipes + 2 * command.id, command, env);
	execute_simple_command(command, env);
}

/// @brief Ensures the relevant pipes are closed in the parent so that the pipes
/// in the child process close properly.
/// @param i The index of the current command.
/// @param num_commands The total number of commands.
/// @param pipes Pointer to the array of pipes.
static void	parent(int i, int num_commands, int *pipes)
{
	int	*pipe_in;
	int	*pipe_out;

	pipe_in = NULL;
	pipe_out = NULL;
	if (i > 0)
		pipe_in = pipes + 2 * (i - 1);
	if (i != num_commands - 1)
		pipe_out = pipes + 2 * i;
	if (pipe_in)
		close(pipe_in[PIPE_READ]);
	if (pipe_out)
		close(pipe_out[PIPE_WRITE]);
}

static int	execute(char **commands, int num_commands, int *pipes,
				t_environment *env)
{
	int			pid;
	t_command	command;
	int			index;

	index = 0;
	while (index < num_commands)
	{
		if (pipe(pipes + 2 * index) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			set_child();
			command = parse_command(index, commands[index], env);
			if (index != num_commands - 1)
				child(command, FALSE, pipes, env);
			else
				child(command, TRUE, pipes, env);
			continue ;
		}
		parent(index, num_commands, pipes);
		index++;
	}
	return (pid);
}

void	handle_pipeline(char **commands, int arrlen, int *pipes,
			t_environment *env)
{
	int	pid;
	int	status;

	status = 0;
	pid = execute(commands, arrlen, pipes, env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_code = WEXITSTATUS(status);
	while (wait(0) > 0)
		continue ;
}
