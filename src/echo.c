/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:44:40 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/06 11:15:40 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_arg(char *str, char **envp, int new_line)
{
	if (new_line)
		ft_putendl_fd(str, STDOUT_FILENO);
	else
		ft_putstr_fd(str, STDOUT_FILENO);
	return (0);
}

int	echo(int argc, char **argv, char **envp)
{
	int	new_line;
	int	index;
	int	exit_code;

	if (argc == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		if (ft_strncmp(argv[1], "-n", 3))
			new_line = 1;
		else
			new_line = 0;
		index = new_line + 1;
		while (index < argc)
		{
			exit_code = process_arg(argv[index++], envp, new_line);
			if (exit_code != 0)
				return (error());
		}
	}
	return (0);
}
