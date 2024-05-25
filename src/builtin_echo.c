/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 08:44:40 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/25 09:58:11 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_flag(char *arg)
{
	while (ft_isspace(*arg))
		arg++;
	if (*arg != '-')
		return (FALSE);
	arg++;
	while (*arg == 'n')
		arg++;
	while (ft_isspace(*arg))
		arg++;
	if (*arg != '\0')
		return (FALSE);
	return (TRUE);
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

	(void) env;
	if (argc == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	else
	{
		index = 1;
		new_line = 1;
		if (is_flag(args[1]))
			new_line = FALSE;
		while (is_flag(args[index]) && index < argc)
			index++;
		while (index < argc)
		{
			ft_putstr_fd(args[index], STDOUT_FILENO);
			index++;
			if (index != argc)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		if (new_line)
			ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
