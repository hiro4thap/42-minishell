/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:13:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/11 22:00:14 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*point_next_simple_command(char *command)
{
	while (*command)
	{
		if (*command == '|')
		{
			command++;
			break ;
		}
		if (is_quote(*command) && ft_strchr(command + 1, *command))
			command = ft_strchr(command + 1, *command);
		command++;
	}
	if (!*command)
		command = NULL;
	return (command);
}

static int	count_simple_commands(char *command)
{
	int	len;

	len = 0;
	while (command && *command)
	{
		len++;
		command = point_next_simple_command(command);
	}
	return (len);
}

// [MALLOC]
static char	*get_current_simple_command(char *command)
{
	char	*start;
	char	*end;
	char	*simple_command;

	if (!command)
		return (NULL);
	start = command;
	if (!point_next_simple_command(command))
		end = ft_strchr(command, '\n');
	else
		end = point_next_simple_command(command);
	simple_command = ft_substr(start, 0, end - start - 1);
	return (simple_command);
}

char	**split_command(char *command)
{
	int		len;
	char	**simple_commands;
	int		i;

	len = count_simple_commands(command);
	simple_commands = malloc((len + 1) * sizeof(char *));
	if (!simple_commands)
		return (NULL);
	i = 0;
	while (i < len)
	{
		simple_commands[i] = get_current_simple_command(command);
		if (!simple_commands[i])
		{
			ft_strarr_clear(simple_commands);
			return (NULL);
		}
		command = point_next_simple_command(command);
		i++;
	}
	simple_commands[i] = NULL;
	return (simple_commands);
}

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
	if (!path)
	{
		perror(envp->shell);
		exit(EXIT_FAILURE);
	}
	dirs = ft_split(path, ':');
	if (!dirs)
	{
		free(path);
		perror(envp->shell);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (dirs[i])
	{
		cmd = ft_strconcat(dirs[i], "/", command.command[0], NULL);
		if (!cmd)
		{
			free(path);
			ft_strarr_clear(dirs);
			perror(envp->shell);
			exit(EXIT_FAILURE);
		}
		execve(cmd, command.command, envp->envp);
		free(cmd);
		i++;
	}
	free(path);
	ft_strarr_clear(dirs);
}
