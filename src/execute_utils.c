/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:13:40 by hiono             #+#    #+#             */
/*   Updated: 2024/06/12 14:34:29 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_directories(t_environment *env)
{
	char	**dirs;
	char	*path;

	if (get_value(env, "PATH"))
		path = ft_strdup(get_value(env, "PATH"));
	else
		path = getcwd(NULL, 0);
	if (!path)
	{
		perror(env->shell);
		exit(EXIT_FAILURE);
	}
	dirs = ft_split(path, ':');
	free(path);
	return (dirs);
}

void	run_file(t_command command, t_environment *env)
{
	char	**dirs;
	char	*cmd;
	int		index;

	dirs = get_directories(env);
	if (!dirs)
	{
		perror(env->shell);
		exit(EXIT_FAILURE);
	}
	index = 0;
	while (dirs[index])
	{
		cmd = ft_strconcat(dirs[index], "/", command.command[0], NULL);
		if (!cmd)
		{
			perror(env->shell);
			ft_strarr_clear(dirs);
			exit(EXIT_FAILURE);
		}
		execve(cmd, command.command, env->envp);
		free(cmd);
		index += 1;
	}
	ft_strarr_clear(dirs);
}
