/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 09:38:44 by jhughes           #+#    #+#             */
/*   Updated: 2024/05/20 11:53:18 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/// @brief Builtin: Displays all environment variables in the terminal.
/// @param env The minishell environment.
/// @return Exit code: 0 on success.
int	builtin_env(t_environment *env)
{
	int	index;

	index = 0;
	while (index < env->size)
		ft_putendl_fd(env->envp[index++], STDOUT_FILENO);
	return (0);
}
