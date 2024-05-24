/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:08:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/24 18:12:27 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Exits the shell with the exit code of that last foreground process.
/// @param env The minishell environment.
/// @return Exit status.
int	builtin_exit(t_environment *env)
{
	int			exit_code;
	const char	*val;

	val = get_value(env, "?");
	exit_code = 0;
	if (val)
		exit_code = ft_atoi(val);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_code);
	return (exit_code);
}
