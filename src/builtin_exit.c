/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:08:57 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/27 00:51:07 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


/// @brief Exits the shell with the exit code of that last foreground process.
/// @param env The minishell environment.
/// @return Exit status.
int	builtin_exit(t_environment *env)
{
	const int	exit_code = env->exit_code;

	if (env->echoctl_was_enabled)
		sig_echo_enable();
	else
		sig_echo_disable();
	ft_strarr_clear(env->envp);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(exit_code);
	return (exit_code);
}
