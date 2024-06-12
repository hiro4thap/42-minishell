/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:14:51 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 10:56:46 by hiono            ###   ########.fr       */
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
		if (!cmd)
		{
			perror(envp->shell);
			exit(EXIT_FAILURE);
		}
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
static int	child(t_command command, int last_command, int *pipes,
	t_environment *env)
{
	int	exit_code;

	if (command.id == 0)
		exit_code = dup_in_fds(NULL, command, command.id, env);
	else
		exit_code = dup_in_fds(pipes + 2 * (command.id - 1), command,
				command.id, env);
	if (exit_code)
		return (exit_code);
	if (last_command)
		exit_code = dup_out_fds(NULL, command, env);
	else
		exit_code = dup_out_fds(pipes + 2 * command.id, command, env);
	if (exit_code)
		return (exit_code);
	execute_simple_command(command, env);
	return (EXIT_SUCCESS);
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
	int			exit_code;

	index = 0;
	while (index < num_commands)
	{
		if (pipe(pipes + 2 * index) == -1)
			return (-1);
		pid = fork();
		if (pid == -1)
			return (-2);
		if (pid == 0)
		{
			set_child();
			if (parse_command(index, commands[index], env, &command))
				return (-3);
			if (index != num_commands - 1)
				exit_code = child(command, FALSE, pipes, env);
			else
				exit_code = child(command, TRUE, pipes, env);
			if (exit_code == EXIT_NO_MEMORY)
				return (-3);
			continue ;
		}
		parent(index, num_commands, pipes);
		index++;
	}
	return (pid);
}

int	handle_pipeline(char **commands, int arrlen, int *pipes,
			t_environment *env)
{
	int	pid;
	int	status;

	status = 0;
	pid = execute(commands, arrlen, pipes, env);
	if (pid == -1)
		return (EXIT_PIPE_FAILURE);
	else if (pid == -2)
		return (EXIT_FORK_FAILURE);
	else if (pid == -3)
		return (EXIT_NO_MEMORY);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_code = WEXITSTATUS(status);
	while (wait(0) > 0)
		continue ;
	return (EXIT_SUCCESS);
}
