/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:44:40 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/13 09:06:39 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_arg(char *str, char **envp, int new_line)
{
	(void) envp;
	if (new_line)
		ft_putendl_fd(str, STDOUT_FILENO);
	else
		ft_putstr_fd(str, STDOUT_FILENO);
	return (0);
}

/// @brief Prints out a string of arguments, evaluating 
/// @param argc 
/// @param argv 
/// @param envp 
/// @return 
int	builtin_echo(int argc, char **args, t_environment *env)
{
	int	new_line;
	int	index;
	int	exit_code;

	if (argc == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		if (ft_strncmp(args[1], "-n", 3))
			new_line = 1;
		else
			new_line = 0;
		index = new_line + 1;
		while (index < argc)
		{
			exit_code = process_arg(args[index++], env->envp, new_line);
			// if (exit_code != 0)
			// 	return (error());
		}
	}
	return (0);
}
